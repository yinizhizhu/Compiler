#include "stdafx.h"
#include "control.h"

int getIndex(char* token)		//return the col of the token in the table
{
	int i = 0;
	for (; i < 199; i++)
		if (strcmp(token, key[i]) == 0)
			return i;
	return -1;
}

void shift(int index, char* token)		//shift, Just shift the token into the table
{
	int x = topStates();
	pushStates( atoi(getContainer(x, index)[1]) );
	pushNames(token);
	return;
}

bool reduce(int index)		//reduce
{
	int i, len;
	int x = topStates(), y=index;
	char** container = getContainer(x, y);
	len = getNum(x, y);
	if (strcmp(container[3], EMPTY) != 0)
	{
		for (i = getNum(x, y); i >= 3; i--)
		{
			if (strcmp(topNames(), container[i]) == 0)
			{
				if (sizeNames() == 0)
					return error();
				popNames();
			}
			else
				return error();
		}
	}
	pushNames(container[1]);
	return go(container[1]);
}

bool go(char* token)			//goto the next state
{
	int x, y;
	x = topStates();
	y = getIndex(token);
	if (getS(x, y) == 3)
	{
		if (getNum(x, y) != -1)
		{
			pushStates(getNum(x, y));
			return true;
		}
		return error();
	}
	else
		return error();
}

bool error()
{
	printf("Syntax error!\n");
	return false;
}

void control()		//control the shift-reduce-accpet
{
	int x, y, s;
	FILE* fp = fopen("in.txt", "r");
	char token[KEY_LENGTH];
	while (fscanf(fp, "%s\n", token) == 1)
	{
		x = topStates();
		y = getIndex(token);
		s = getS(x, y);
		if (s == -1)
		{
			printf("Syntax error!\n");
			return;
		}
		else if (s == 0)
		{
			printf("ACCEPT!\n");
			return;
		}
		else if (s == 1)
		{
			while (s == 1)
			{
				reduce(y);
				x = topStates();
				s = getS(x, y);
			}
		}
		else if (s == 2)
			shift(y, token);
	}
	fclose(fp);
	return;
}

int main()
{
	initStates();
	initNames();
	initTable();


	testStates();
	testNames();
	testTable();

	freeTable();
	freeNames();
	freeStates();
	return 0;
}