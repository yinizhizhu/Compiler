#include "stdafx.h"
#include "control.h"

int getIndex(char* token)		//return the col of the token in the table
{
	int i = 1;
	for (; i < 200; i++)
		if (strcmp(token, key[i]) == 0)
			return i;
	return -1;
}

void shift(int index, char* token)		//shift, Just shift the token into the table
{
	int x = topStates();

	fprintf(out, "shift %s\n", getContainer(x, index)[0]); //container[0], token
	
	pushStates( atoi(getContainer(x, index)[0]) );
	pushNames(token);
	//printf("The size of states: %d, %d, the size of names: %d, %s\n", sizeStates(), topStates(), sizeNames(), topNames());
	return;
}

bool reduce(int index)		//reduce
{
	int i;
	int x = topStates(), y=index;
	char** container = getContainer(x, y);

	fprintf(out, "reduce ");
	for (i = 0; i < getNum(x, y); i++) //output the production
		fprintf(out, "%s ", container[i]);
	fprintf(out, "\n");
	
	if (strcmp(container[2], EMPTY) != 0)	//the production contain the nonempty string
	{
		for (i = (getNum(x, y)-1); i >= 2; i--)		//process of reducing
		{
			if (strcmp(topNames(), container[i]) == 0)
			{
				if (sizeNames() == 0)
					return error("the stack is empty");
				popNames();
				popStates();
			}
			else
				return error("no matching string bettween stack and production");
		}
	}
	pushNames(container[0]);
	return go(container[0]);
}

bool go(char* token)			//goto the next state
{
	int x, y;
	x = topStates();
	y = getIndex(token);
	if (getS(x, y) == 3)	//the action of goto
	{
		if (getNum(x, y) != -1)		//right for the goto
		{
			pushStates(getNum(x, y));
			return true;
		}
		return error("the position is null in goto table");
	}
	else	//the state is not goto
		return error("the state is not 3 for goto");
}

bool error(char* info)
{
	fprintf(out, "Syntax error: %s!\n", info);
	return false;
}

void control()		//control the shift-reduce-accpet
{
	int x, y, s;
	FILE* fp = fopen("sample.txt", "r");
	char token[KEY_LENGTH];
	while (fscanf(fp, "%s", token) == 1)
	{
	LABEL:
		fprintf(out, "\nThe input token is: %s\n", token);
		x = topStates();
		y = getIndex(token);
		if (y < 0)
		{
			fprintf(out, "Syntax error!\n");
			fclose(fp);
			return;
		}
		s = getS(x, y);
		showNames();
		showStates();
		if (s == -1)	//error
		{
			fprintf(out, "Syntax error: action is wrong!\n");
			fclose(fp);
			return;
		}
		else if (s == 0)	//error accept
		{
			fprintf(out, "ACCEPT before end! Syntax error\n");
			fclose(fp);
			return;
		}
		else if (s == 1)	//reduce the production
		{
			if (!reduce(y))
			{
				fprintf(out, "Reduce is error!\n");
				fclose(fp);
				return;
			}
			goto
				LABEL;	//we keep this token to continue to judge
		}
		else if (s == 2)	//shift the token
			shift(y, token);
		else		//the state is wrong for 3, no need to go to the next state
		{
			fprintf(out, "Syntax error: state equal 3, but no need to goto!\n");
			fclose(fp);
			return;
		}
	}
	printf("The last step!\n");
	x = topStates();
	y = getIndex("$");
	if (getS(x, y) == 0)
		fprintf(out, "ACCEPT!\n");
	else
		fprintf(out, "Syntax error!\n");
	fclose(fp);
	return;
}

void testKey()
{
	int j;
	for (j = 0; j < 66; j++)
		if (getNum(7, j) > 0)
			printf("%s %d: %d\n", key[j], j, getNum(7, j));
	printf("\n");
}

int main()
{
	//int i, j;
	initStates();
	initNames();
	initTable();

	//testStates();
	//testNames();
	//testTable();
	//testKey();

	out = fopen("process.txt", "w");
	control();
	fclose(out);

	//for (i = 0; i < ROOM_ROW; i++)
	//	for (j = 1; j < ROOM_COL; j++)
	//	{
	//		if (table[i][j].state == 2)
	//			printf("%d, %d: %s\n", i, j, getContainer(i, j)[0]);
	//	}
	freeTable();
	freeNames();
	freeStates();
	return 0;
}