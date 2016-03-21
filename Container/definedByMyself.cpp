#include "stdafx.h"

void stirng_tolower(char *arr)		//To change the string the lower string
{
	int i;
	for (i = 0; i < (int)strlen(arr); i++)
		arr[i] = tolower(arr[i]);
	return;
}

void string_toupper(char *arr)		//To change the string the lower string
{
	int i;
	for (i = 0; i < (int)strlen(arr); i++)
		arr[i] = toupper(arr[i]);
	return;
}

bool isDigit(char c)		//return true while c is a digit
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool isAlpha(char c)		//return true while c is a letter
{
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}
