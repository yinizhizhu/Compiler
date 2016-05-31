#pragma once
#if !defined LRTABLE_H
#define LRTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROOM_ROW 2230	//2289
#define ROOM_COL 200	//199
#define STRING_LENGTH 42

#define REDUCE "reduce"
#define SHIFT "shift"
#define ACCEPT "accept"
#define ERROR_ "-1"
#define LEE "Lee"
#define EMPTY "¦Å"

typedef struct td
{
	int state;		//reduce(1), shift(2), accept(0), error(-1), Lee(-2), goto(3)
	int num;		//the number of the string
	char** container;		//container of the string
} Td;
Td** table;

void initTable();		//let the table initial
void readTable();		//read the table from the file("LRTable.txt")
void insertTd(char container[20][STRING_LENGTH], int* row, int* col, int move);		//Insert the production into the table according the state
int validXY(int row, int col);
int getS(int row, int col);	//return the state with x&y
int getNum(int row, int col);	//return the number of the string with x&y
char** getContainer(int row, int col);	//return the container with x&y
void freeTable();		//free the room for the table

void testTable();
#endif