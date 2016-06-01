#pragma once
#if !defined STATEMENTQUEUE_H
#define STATEMENTQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "threeAddress.h"
#define NAMELEN 30

addressCode *nStatement;	//store the token appeared according to the order of appearing

void initStatement();
int sizeStatement();				//the size of the queue
bool emptyStatement();				//judge whether the queue is empty or not
addressCode *frontStatement();			//the front of the queue
addressCode *backStatement();				//the back of the queue
void pushStatement(int op, char *a1, char *a2, char *a3);	//push the token into the queue
void popStatement();				//delete the head of the queue
void clearStatement();				//delete all tokens in the queue
void showStatement();
void testStatement();

#endif