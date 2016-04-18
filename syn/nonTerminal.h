#pragma once
#if !defined NONTERMINAL_H
#define NONTERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROOM_N 3000
#define CHAE_LENGTH 42

typedef struct name{
	char val[CHAE_LENGTH];
} Name;

Name* names;
int nameTop;

void initNames();	//to let the names initial
void pushNames(const char* string);	//push the 'string' into the names
void popNames();		//pop the top of the names
char* topNames();	//return the top string of the names
int sizeNames();		//return the size of the names
void showNames();
void testNames();
void freeNames();	//free the room for names

#endif