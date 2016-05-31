#pragma once
#if !defined SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H

#include <stdio.h>
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "state.h"
#include "lrTable.h"
#include "nonTerminal.h"

#define KEY_COL 200	//1~199
#define KEY_LENGTH 42

bool control();		//control the shift-reduce-accpet
int getIndex(char* token);		//return the col of the token in the table
void shift(int index, char* token);		//shift, Just shift the token into the table
bool reduce(int index);		//reduce
bool go(char* token);			//goto the next state
bool synError(char* info);
void testKey();

FILE* out;

#endif