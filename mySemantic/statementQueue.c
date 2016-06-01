#include "statementQueue.h"

void initStatement()
{
	nStatement = NULL;
	return;
}

int sizeStatement()
{
	int counter = 0;
	addressCode *head = frontStatement();
	while (head)
	{
		head = head->next;
		counter++;
	}
	return counter;
}

bool emptyStatement()
{
	if (sizeStatement() == 0)
		return true;
	return false;
}

addressCode *frontStatement()
{
	return nStatement;
}

addressCode *backStatement()
{
	addressCode *move = frontStatement();
	if (move == NULL)
		return NULL;
	while (move->next)
		move = move->next;
	return move;
}

void pushStatement(int op, char *a1, char *a2, char *a3)
{
	addressCode *value = (addressCode*)malloc(sizeof(addressCode));
	if (value == NULL)
	{
		printf("The room is not enough for value!\n");
		return;
	}
	value->op = op;
	strcpy(value->A1, a1);
	strcpy(value->A2, a2);
	strcpy(value->A3, a3);
	addressCode *last = backStatement();
	if (last == NULL)
		nStatement = value;
	else
		last->next = value;
	return;
}

void popStatement()
{
	addressCode *head = frontStatement();
	if (head == NULL)
		return;
	nStatement = nStatement->next;
	free(head);
	return;
}

void clearStatement()
{
	addressCode *head = frontStatement();
	while (head)
	{
		nStatement = nStatement->next;
		free(head);
		head = frontStatement();
	}
	return;
}

void showStatement()
{
	addressCode *move = frontStatement();
	printf("op	A1	A2	A3\n");
	while (move)
	{
		printf("%d	%s	%s	%s\n", move->op, move->A1, move->A2, move->A3);
		move = move->next;
	}
	return;
}

void testStatement()
{
	return;
}

