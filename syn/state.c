#include "state.h"

void initStates() //let the states initial
{
	stateTop = -1;
	states = NULL;
	states = (int*)malloc(ROOM_S*sizeof(int));
	if (states == NULL)
	{
		printf("Not enough room for the states!\n");
		freeStates();
		return;
	}
	pushStates(0);
	printf("Get the room for states!\n");
	return;
}

void pushStates(const int move) //push the 'move' into the states
{
	if ((stateTop+1) >= ROOM_S)
	{
		printf("The stack of State is overflow!\n");
		return;
	}
	states[++stateTop] = move;
	return;
}

void popStates() //pop the top of the states
{
	if (stateTop == -1)
	{
		printf("The stack of State is empty!\n");
		return;
	}
	--stateTop;
	return;
}

int topStates() //return the top of the states
{
	if (stateTop == -1)
	{
		printf("The stack of name is empty!\n");
		return -2;
	}
	return states[stateTop];
}

int sizeStates() //return the size of the states have be stored
{
	return (stateTop+1);
}

void showStates()
{
	int i;
	for (i = 0; i <= stateTop; i++)
		printf("%d ", states[i]);
	printf("\n");
}

void showStatesFile(FILE* out)
{
	int i;
	for (i = 0; i <= stateTop; i++)
		fprintf(out, "%d ", states[i]);
	fprintf(out, "\n");
}

void testStates()
{
	int j = 1;
	for (; j < 10; j++)
	{
		pushStates(j);
		printf("%d\n", sizeStates());
		showStates();
	}
	for (j = 1; j < 10; j++)
	{
		popStates();
		printf("%d\n", sizeStates());
		showStates();
	}
	popStates();
	return;
}

void freeStates() //free the room for the states
{
	free(states);
	printf("Free the room for states!\n");
	return;
}
