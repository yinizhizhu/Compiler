// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include <stdio.h>
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
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