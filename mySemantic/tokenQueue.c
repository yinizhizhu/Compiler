#include "tokenQueue.h"

void initQueue()
{
	tokenQueue = NULL;
	return;
}

int sizeQueue()
{
	int size = 0;
	token *tmp = tokenQueue;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return size;
}

bool emptyQueue()
{
	if (sizeQueue() == 0)
		return true;
	return false;
}

token *frontQueue()
{
	if (sizeQueue() == 0)
	{
		printf("The queue is empty!\n");
		return NULL;
	}
	return tokenQueue;
}

token *backQueue()
{
	if (sizeQueue() == 0)
	{
		printf("The queue is empty!\n");
		return NULL;
	}
	token *tmp = tokenQueue;
	while (tmp->next)
		tmp = tmp->next;
	return tmp;
}

void pushQueue(char *value)
{
	if (sizeQueue() == 0)
	{
		tokenQueue = (token*)malloc(sizeof(token));
		if (tokenQueue == NULL)
		{
			printf("The room is not eough for tokenQueue!\n");
			return;
		}
		strcpy(tokenQueue->value, value);
		tokenQueue->next = NULL;
		return;
	}
	token *backOne = backQueue();
	backOne->next = (token*)malloc(sizeof(token));
	backOne = backOne->next;
	if (backOne == NULL)
	{
		printf("The room is not eough for new part of queue!\n");
		return;
	}
	strcpy(backOne->value, value);
	backOne->next = NULL;
	return;
}

void popQueue()
{
	token *head = frontQueue();
	if (head == NULL)
	{
		printf("The queue is empty already!\n");
		return;
	}
	tokenQueue = tokenQueue->next;
	free(head);
	return;
}

void clearQueue()
{
	token *head = frontQueue();
	if (head == NULL)
		return;
	while (head)
	{
		tokenQueue = tokenQueue->next;
		free(head);
		head = frontQueue();
	}
	return;
}

void showQueue()
{
	token *head = frontQueue();
	while (head)
	{
		printf("%s ", head->value);
		head = head->next;
	}
	printf("\n");
	return;
}

void testQueue()
{
	pushQueue("we");
	pushQueue("are");
	pushQueue("the");
	pushQueue("champion");
	pushQueue("!");

	while (!emptyQueue())
	{
		showQueue();
		printf("Pop the front of queue: %s\n", frontQueue()->value);
		popQueue();
	}

	pushQueue("we");
	pushQueue("are");
	pushQueue("the");
	pushQueue("champion");
	pushQueue("!");

	showQueue();
	clearQueue();
	printf("After clearing:\n");
	showQueue();
	
	return;
}
