#pragma once
#if !defined TOKENQUEUE_H
#define TOKENQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NAMELEN 30

typedef struct token
{
	char value[NAMELEN];
	struct token *next;
}token;

token *tokenQueue;	//store the token appeared according to the order of appearing

void initQueue();
int sizeQueue();				//the size of the queue
bool emptyQueue();				//judge whether the queue is empty or not
token *frontQueue();			//the front of the queue
token *backQueue();				//the back of the queue
void pushQueue(char *value);	//push the token into the queue
void popQueue();				//delete the head of the queue
void clearQueue();				//delete all tokens in the queue
void showQueue();
void testQueue();

#endif