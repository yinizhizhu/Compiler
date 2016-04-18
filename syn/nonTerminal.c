#include "nonTerminal.h"

void initNames() //to let the names initial
{
	nameTop = -1;
	names = NULL;
	names = (Name*)malloc(ROOM_N*sizeof(Name));
	if (names == NULL)
	{
		printf("Not enough room for the names!\n");
		freeNames();
		return;
	}
	pushNames("#");
	printf("Get the room for names!\n");
 	return;
}

void pushNames(const char* string) //push the 'string' into the names
{
	if ((nameTop+1) >= ROOM_N)
	{
		printf("The stack of Name is overflow!\n");
		return;
	}
	strcpy(names[++nameTop].val, string);
	return;
}

void popNames() //pop the top of the names
{
	if (nameTop == -1)
	{
		printf("The stack of Name is empty!\n");
		return;
	}
	--nameTop;
	return;
}

char* topNames() //return the top string of the names
{
	if (nameTop == -1)
	{
		printf("The stack of name is empty!\n");
		return NULL;
	}
	return names[nameTop].val;
}

int sizeNames() //return the size of the names
{
	return (nameTop+1);
}

void showNames()
{
	int i = 0;
	for (; i <= nameTop; i++)
		printf("%s ", names[i].val);
	printf("\n");
}

void testNames()
{
	int i = 0;
	pushNames("my_name");
	showNames();
	pushNames("hehe-dada");
	showNames();
	for (; i < 4; i++)
	{
		popNames();
		showNames();
	}
}

void freeNames() //free the room for names
{
	free(names);
	printf("Free the room for names!\n");
	return;
}