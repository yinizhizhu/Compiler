#include "stdafx.h"

void stirng_tolower(char *arr)		//To change the string the lower string
{
	int i;
	for (i = 0; i < (int)strlen(arr); i++)
		arr[i] = tolower(arr[i]);
	return;
}
