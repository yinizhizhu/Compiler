#include "threeAddress.h"

bool initThreeAddress(int op, char *a1, char *a2, char *a3)			//initial the threeAddress
{
	threeAddress = NULL;
	threeAddress = (addressCode*)malloc(sizeof(addressCode));
	if (threeAddress == NULL)
	{
		printf("The room is not eough for new part of threeAddress!\n");
		return false;
	}
	threeAddress->op = op;
	strcpy(threeAddress->A1, a1);
	strcpy(threeAddress->A2, a2);
	strcpy(threeAddress->A3, a3);
	threeAddress->next = NULL;
	return true;
}

void initThreeAddressP(addressCode *p)
{
	threeAddress = NULL;
	threeAddress = p;
	return;
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
	{
		printf("The room is not eough for new part of address tmp!\n");
		return false;
	}
	tmp->op = op;
	strcpy(tmp->A1, a1);
	strcpy(tmp->A2, a2);
	strcpy(tmp->A3, a3);
	tmp->next = NULL;
	last->next = tmp;
	return true;
}

void insertThreeAddressP(addressCode *p)
{
	if (threeAddress == NULL)
	{
		initThreeAddressP(p);
		return;
	}
	addressCode *last = getLast();
	last->next = p;
	return;
}

void showThreeAddress()												//show the content of the threeAddress
{
	FILE *out = fopen("threeCode.txt", "w");
	addressCode *move = threeAddress;
	printf("op	A1	A2	A3\n");
	while (move)
	{
		fprintf(out, "%d	%s	%s	%s\n", move->op, move->A1, move->A2, move->A3);
		printf("%d	%s	%s	%s\n", move->op, move->A1, move->A2, move->A3);
		move = move->next;
	}
	fclose(out);
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
