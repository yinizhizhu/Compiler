#pragma once
#if !defined SEMANTICANALYSIS_H
#define SEMANTICANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SyntaxAnalysis.h"
#include "LexicalAnalysis.h"
#define NAMELEN 30

typedef struct addressCode
{
	int op;		//the code the operator
	char A1[NAMELEN];
	char A2[NAMELEN];
	char A3[NAMELEN];
	struct addressCode *next;
}addressCode;

bool initThreeAddress(int op, char *a1, char *a2, char *a3);
addressCode *getLast();
bool insertThreeAddress(int op, char *a1, char *a2, char *a3);
void showThreeAddress();
void delThreeAddress();
void testS();// test whether the symbol table is good to use or not

#endif