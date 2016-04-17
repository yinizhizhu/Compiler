#pragma once
#if !defined DEFINEDBYMYSELF
#define DEFINEDBYMYSELF
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void stirngTolower(char *arr);
void stringToupper(char *arr);
bool isDigit(char c);
bool isAlpha(char c);

#endif