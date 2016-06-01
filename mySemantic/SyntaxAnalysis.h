#pragma once
#if !defined SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "state.h"
#include "lrTable.h"
#include "nonTerminal.h"
#include "threeAddress.h"
#include "tokenQueue.h"
#include "statementQueue.h"

#define KEY_COL 200	//1~199
#define KEY_LENGTH 42

void setTag(char* word);
bool control();		//control the shift-reduce-accpet
int getIndex(char* word);		//return the col of the token in the table
void shift(int index, char* word);		//shift, Just shift the token into the table

void popT(int n);
void assignmentT(int x, int y, char** container);
void relopT(int x, int y, char** container);
void addopT(int x, int y, char** container);
void ifT(int x, int y, char** container);
void fortoT(int x, int y, char** container);
void translate(int x, int y, char** container);

bool reduce(int index);		//reduce
bool go(char* word);			//goto the next state
bool synError(char* info);
void testKey();

FILE* out;

#endif