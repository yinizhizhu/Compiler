#pragma once
#if !defined LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include <stdio.h>
// TODO:  在此处引用程序需要的其他头文件
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "code.h"
#include "symbolManager.h"
#include "definedByMyself.h"

//const char KEY_WORDS[ALL_KEY][TYPE_LENGTH] = { "",
//"AND", "ARRAY", "PBEGIN", "CASE",
//"CONST", "DIV", "DO", "DOWNTO",
//"ELSE", "END", "PFILE", "FOR",
//"FUNCTION", "GOTO", "IF", "IN",
//"LABEL", "MOD", "NIL", "NOT",
//"OF", "OR", "PACKED", "PROCEDURE",
//"PROGRAM", "RECORD", "REPEAT", "SET",
//"THEN", "TO", "TYPE", "UNTIL",
//"VAR", "WHILE", "WITH", "IDENTIFIER",
//"INT", "REALNUMBER", "CHARACTER_STRING", "PLUS",
//"MINUS", "STAR", "SLASH", "EQUAL",
//"LT", "GT", "LE", "GE",
//"NOTEQUAL", "LPAREN", "RPAREN", "COMMA",
//"P_MARK", "DOT", "DOTDOT", "COLON",
//"ASSIGNMENT", "SEMICOLON", "UPARROW", "STARSTAR",
//"LBRAC", "RBRAC", "Q_MARK", "INTEGER",
//"WORD" };

void handle();	//To get the upper and lower of key words
bool isSeparator(char getChar);	//return "true" while separator
void output(int index, char temp, FILE* out);
void readProgram();		//Read the program from source file.
int lex();

#endif