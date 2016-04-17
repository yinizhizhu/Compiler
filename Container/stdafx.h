// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <stdio.h>
// TODO:  在此处引用程序需要的其他头文件
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "code.h"
#include "Trie.h"
#include "symbolManager.h"
#include "definedByMyself.h"

const char KEY_WORDS[ALL_KEY][TYPE_LENGTH] = { "",
"AND", "ARRAY", "PBEGIN", "CASE",
"CONST", "DIV", "DO", "DOWNTO",
"ELSE", "END", "PFILE", "FOR",
"FUNCTION", "GOTO", "IF", "IN",
"LABEL", "MOD", "NIL", "NOT",
"OF", "OR", "PACKED", "PROCEDURE",
"PROGRAM", "RECORD", "REPEAT", "SET",
"THEN", "TO", "TYPE", "UNTIL",
"VAR", "WHILE", "WITH", "IDENTIFIER",
"INT", "REALNUMBER", "CHARACTER_STRING", "PLUS",
"MINUS", "STAR", "SLASH", "EQUAL",
"LT", "GT", "LE", "GE",
"NOTEQUAL", "LPAREN", "RPAREN", "COMMA",
"P_MARK", "DOT", "DOTDOT", "COLON",
"ASSIGNMENT", "SEMICOLON", "UPARROW", "STARSTAR",
"LBRAC", "RBRAC", "Q_MARK", "INTEGER",
"WORD" };