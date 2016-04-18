#pragma once
#if !defined STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#define ROOM_S 3000

int* states;	//to store the state in the stack
int stateTop;	//the top of the stack of state

void initStates();		//let the states initial
void pushStates(const int move);		//push the 'move' into the states
void popStates();	//pop the top of the states
int topStates();		//return the top of the states
int sizeStates();	//return the size of the states have be stored
void showStates();
void testStates();
void freeStates();	//free the room for the states

#endif