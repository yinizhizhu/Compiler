#include "semanticAnalysis.h"

addressCode *threeAddress = NULL;

bool initThreeAddress(int op, char *a1, char *a2, char *a3)			//initial the threeAddress
{
	threeAddress = (addressCode*)malloc(sizeof(addressCode));
	if (threeAddress == NULL)
		return error("threeAddress");
	threeAddress->op = op;
	strcpy(threeAddress->A1, a1);
	strcpy(threeAddress->A2, a2);
	strcpy(threeAddress->A3, a3);
	threeAddress->next = NULL;
	return true;
}

addressCode *getLast()
{
	addressCode *tmp = threeAddress;
	while (tmp->next)
		tmp = tmp->next;
	return tmp;
}

bool insertThreeAddress(int op, char *a1, char *a2, char *a3)		//insert each expression into the threeAddress
{
	if (threeAddress == NULL)
		return initThreeAddress(op, a1, a2, a3);
	addressCode *last = getLast();
	addressCode *tmp = (addressCode*)malloc(sizeof(addressCode));
	if (tmp == NULL)
		return error("address tmp");
	tmp->op = op;
	strcpy(tmp->A1, a1);
	strcpy(tmp->A2, a2);
	strcpy(tmp->A3, a3);
	tmp->next = NULL;
	last->next = tmp;
	return true;
}

void showThreeAddress()												//show the content of the threeAddress
{
	addressCode *move = threeAddress;
	printf("op	A1	A2	A3\n");
	while (move)
	{
		printf("%d	%s	%s	%s\n", move->op, move->A1, move->A2, move->A3);
		move = move->next;
	}
	return;
}

void delThreeAddress()												//free the resource we get from the system
{
	printf("Free the threeAddress!\n");
	addressCode *tmp = threeAddress;
	while (threeAddress)
	{
		threeAddress = threeAddress->next;
		free(tmp);
		tmp = threeAddress;
	}
	return;
}

void testS()// test whether the symbol table is good to use or not
{
	showSymbolList();
	return;
}