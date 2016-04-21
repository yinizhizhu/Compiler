#pragma once
#if !defined SYMBOLMANAGER_H
#define SYMBOLMANAGER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NAME_CONTAINER_LENGTH 10000	//the length of the container of name

#define N 256
#define BUFFER 2048
#define PRIME 211
#define EOS '\0'
#define SYMBOL_LIST_LENGTH 211	//the length of the hash(in symbol list)

typedef unsigned int u_int;

typedef struct extendPro	//the extend priority of the symbol list
{
	int dimensionNum;		// the number of the dimension
	int* dimensions;		// container of the dimensions
} extendP;

typedef struct symbolNode	//the symbol list
{
	char* name;				//the name of variable
	int typeB;				//the type of the variable: array, string or variable
	int typeS;				//the main type: int, float, real and so on.
	u_int address;			//the address of the variable
	extendP* properties;	//the extend properties
	struct symbolNode* next;
} symbolN;

symbolN** symbolList;
bool initSymbolList();
int hashPJW(char* s);	//get the index of the string in the hash table of symbol list
symbolN* getSymbolN(char* s);
bool insertIntoSymbolList(char* name);		//insert the identifier into the symbol list with the name of identifier
bool insertIntoSymbolList2(char* name, int typeB, int typeS, u_int address);		//insert the identifier into the symbol list with name, typeB...
bool insertIntoSymbolList3(char* name, int typeB, int typeS, u_int address, int* nextP, int lenP);		//insert the identifier into the symbol list with name, typeB...
bool error(char* info);
void delSymbolList();

#endif