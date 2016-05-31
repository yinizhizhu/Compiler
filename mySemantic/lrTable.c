#include "lrTable.h"

void initTable() //let the table initial
{
	int i, j;
	table = NULL;
	table = (Td**)malloc(ROOM_ROW*sizeof(Td*));
	if (table == NULL)
	{
		printf("Not enough room for the table!\n");
		freeTable();
		return;
	}
	for (i = 0; i < ROOM_ROW; i++)
	{
		table[i] = (Td*)malloc(ROOM_COL*sizeof(Td));
		if (table[i] == NULL)
		{
			printf("Not enough room for the table[i]!\n");
			freeTable();
			return;
		}
		for (j = 0; j < ROOM_COL; j++)
		{
			table[i][j].state = -1;
			if (j <= 65)	//terminal token
				table[i][j].num = 0;
			else	//nonterminal token
				table[i][j].num = -1;
			table[i][j].container = NULL;
		}
	}
	printf("Get the room for table!\n");
	readTable();
	return;
}

void readTable() //read the table from the file("LRTable.txt")
{
	int row = 0, col = 0;
	int move = 0, index = 0;
	char tmp, container[20][STRING_LENGTH];
	FILE* fp = fopen("LRTable.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open the table file!\n");
		return;
	}
	tmp = fgetc(fp);
	while (tmp != EOF)
	{
		if (tmp == ' ')
		{
			if (index > 0)
			{
				container[move++][index] = 0;
				index = 0;
			}
		}
		else if (tmp == '\n')
		{
			if (index > 0)
				container[move++][index] = 0;
			insertTd(container, &row, &col, move);
			move = index = 0;
		}
		else
			container[move][index++] = tmp;
		tmp = fgetc(fp);
	}
	fclose(fp);
	return;
}

void insertTd(char container[10][STRING_LENGTH], int* row, int* col, int move) //Insert the production into the table according the state
{
	int i, len=move-1;
	int x = *row, y = *col;
	if (move <= 0)
		return;
	if (x < 0 || x > ROOM_ROW || y < 0 || y > ROOM_COL)
		return;
	if (strcmp(REDUCE, container[0]) == 0)
	{
		table[x][y].state = 1;
		table[x][y].num = len;
		table[x][y].container = (char**)malloc(len*sizeof(char*));
		if (table[x][y].container == NULL)
		{
			printf("Not enough room for the table[x][y].container!\n");
			freeTable();
			return;
		}
		for (i = 0; i < len; i++)
		{
			table[x][y].container[i] = (char*)malloc(STRING_LENGTH*sizeof(char));
			if (table[x][y].container[i] == NULL)
			{
				printf("Not enough room for the table[x][y].container[i]!\n");
				freeTable();
				return;
			}
			strcpy(table[x][y].container[i], container[i + 1]);
		}
		(*col)++;
	}
	else if (strcmp(SHIFT, container[0]) == 0)
	{
		table[x][y].state = 2;
		table[x][y].num = len;
		table[x][y].container = (char**)malloc(len*sizeof(char*));
		if (table[x][y].container == NULL)
		{
			printf("Not enough room for the table[x][y].container!\n");
			freeTable();
			return;
		}
		table[x][y].container[0] = (char*)malloc(STRING_LENGTH*sizeof(char));
		if (table[x][y].container[0] == NULL)
		{
			printf("Not enough room for the table[x][y].container[0]!\n");
			freeTable();
			return;
		}
		strcpy(table[x][y].container[0], container[1]);
		(*col)++;
	}
	else if (strcmp(ACCEPT, container[0]) == 0)
	{
		table[x][y].state = 0;
		(*col)++;
	}
	else if (strcmp(ERROR_, container[0]) == 0)
	{
		table[x][y].state = -1;
		(*col)++;
	}
	else if (strcmp(LEE, container[0]) == 0)
	{
		//printf("%d, %d\n", x, y);
		(*row)++;
		*col = 0;
	}
	else
	{
		table[x][y].state = 3;
		table[x][y].num = atoi(container[0]);
		(*col)++;
	}
	return;
}

int validXY(int row, int col)
{
	if (row >= 0 && row < ROOM_ROW && col >= 0 && col < ROOM_COL)
		return 1;
	return 0;
}

int getS(int row, int col)	//return the state with x&y
{
	if (validXY(row, col))
		return table[row][col].state;
	return INT_MIN;
}

int getNum(int row, int col)	//return the number of the string with x&y
{
	if (validXY(row, col))
		return table[row][col].num;
	return INT_MIN;
}

char** getContainer(int row, int col)	//return the container with x&y
{
	if (validXY(row, col))
		return table[row][col].container;
	return NULL;
}

void freeTable() //free the room for the table
{
	int i, j, k;
	for (i = 0; i < ROOM_ROW; i++)
	{
		for (j = 0; j < ROOM_COL; j++)
		{
			if (table[i][j].container)
			{
				for (k = 0; k < table[i][j].num; k++)
					free(table[i][j].container[k]);
				free(table[i][j].container);
			}
		}
		free(table[i]);
	}
	free(table);
	printf("Free the room for table!\n");
	return;
}

void testTable()
{
	int j = 0;
	char** tmp;
	printf("%d:\n", getS(0, 45));
	tmp = getContainer(0, 45);
	for (; j < getNum(0, 45); j++)
		printf("%s %d\n", tmp[j], strlen(tmp[j]));
	//for (; j < ROOM_COL; j++)
	//	printf("%d\n", table[0][j].state);
}