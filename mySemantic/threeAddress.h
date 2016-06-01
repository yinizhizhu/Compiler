#pragma once
#if !defined SEMANTICANALYSIS_H
#define SEMANTICANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NAMELEN 30

typedef struct addressCode
{
	int op;		//the code the operator: 0-":=", 1-"+", 2-"-", 3-"*", 4-"/", 5-">", 6-"<", 7-"=", 8-"<>"
	char A1[NAMELEN];
	char A2[NAMELEN];
	char A3[NAMELEN];
	struct addressCode *next;
}addressCode;
addressCode *threeAddress;

bool initThreeAddress(int op, char *a1, char *a2, char *a3);
void initThreeAddressP(addressCode *p);
addressCode *getLast();
bool insertThreeAddress(int op, char *a1, char *a2, char *a3);
void insertThreeAddressP(addressCode *p);
void showThreeAddress();
void delThreeAddress();

#endif