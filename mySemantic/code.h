#pragma once
#if !defined CODE_H
#define CODE_H

#include <string.h>
#include <stdbool.h>
//The code of tokens
#define AND 1
#define ARRAY 2
#define BEGIN 3
#define CASE 4
#define CONST 5
#define DIV 6
#define DO 7
#define DOWNTO 8
#define ELSE 9
#define END 10
#define FILE_ 11
#define FOR 12
#define FUNC 13
#define GOTO 14
#define IF 15
#define IN 16
#define LABEL 17
#define MOD 18
#define NIL 19
#define NOT 20
#define OF 21
#define OR 22
#define PACKED 23
#define PROC 24
#define PROG 25
#define RECORD 26
#define REPEAT 27
#define SET 28
#define THEN 29
#define TO 30
#define TYPE 31
#define UNTIL 32
#define VAR 33
#define WHILE 34
#define WITH 35
#define ID 36
#define INT 37
#define REAL 38
#define STRING 39
#define PLUS 40
#define MINUS 41
#define MULTI 42
#define RDIV 43
#define EQ 44
#define LT 45
#define GT 46
#define LE 47
#define GE 48
#define NE 49
#define LR_BRAC 50
#define RR_BRAC 51
#define COMMA 52
#define P_MARK 53
#define F_STOP 54
#define RANGE 55
#define COLON 56
#define ASSIGN 57
#define SEMIC 58
#define CAP 59
#define EXP 60
#define LS_BRAC 61
#define RS_BRAC 62
#define Q_MARK 63

#define ALL_KEY 64				//the total number of the key_word
#define TYPE_LENGTH 42			//the length of the key word

#define KEY_LEGNTH 39

int searchStr(const char *s);

#endif