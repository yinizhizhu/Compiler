#include "code.h"

const char key_words[KEY_LEGNTH][TYPE_LENGTH] = { "",
"and", "array", "begin", "case",
"const", "div", "do", "downto",
"else", "end", "pfile", "for",
"function", "goto", "if", "in",
"label", "mod", "nil", "not",
"of", "or", "packed", "procedure",
"program", "record", "repeat", "set",
"then", "to", "type", "until",
"var", "while", "with","integer",
"word",  "char"};

int searchStr(const char *s)  //searcht the string
{
	int i;
	for (i = 0; i < KEY_LEGNTH-2; i++)
		if (strcmp(key_words[i], s) == 0)
			return i;
	for (; i < KEY_LEGNTH; i++)
		if (strcmp(key_words[i], s) == 0)
			return 36;
	return -1;
}
