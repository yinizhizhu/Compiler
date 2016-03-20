#include "stdafx.h"

const int N = 100;

void handle()
{
	FILE* fp = fopen("help.txt", "r");
	char temp[N];
	int i, pos = 0;
	for (i = 1; i < 64; i++)
	{
		fscanf(fp, "#define %s %d\n", temp, &pos);
		printf("%s\n", temp);
	}
	fclose(fp);
	return;
}

bool isSeparator(char getChar)
{
	switch (getChar)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '=':
	case ':':
	case '[':
	case ']':
	case '{':
	case '}':
	case '.':
	case '\'':
	case '"':
	case ';':
	case ',':
	case '^':
		return true;
	default:
		return false;
		break;
	}
}

void readProgram()
{
	FILE* fp = fopen("program.txt", "r");
	char temp[N];
	char getChar;
	int pos=0;
	while (!feof(fp))
	{
		getChar = fgetc(fp);
		if (isSeparator(getChar))
		{
			if (pos == 0)
				continue;
			temp[pos] = '\0';
			printf("%s\n", temp);
			pos = 0;
		}
		else if (getChar == ' ' || getChar == '\n')
		{
			if (pos == 0)
				continue;
			temp[pos] = '\0';
			printf("%s\n", temp);
			pos = 0;
		}
		else
			temp[pos++] = getChar;
	}
	fclose(fp);
	return;
}

int main()
{
	//handle();
	//readProgram();
	FILE* fp = fopen("help.txt", "r");
	container = fread(temp, 1, 4, fp);
	temp[4] = '\0';
	for (i = 0; i < strlen(temp); i++)
	{
		printf("%c", temp[i]);
	}
	container = fread(temp, 1, 4, fp);
	temp[4] = '\0';
	printf("\n%d\n", container);
	for (i = 0; i < strlen(temp); i++)
	{
		printf("%c", temp[i]);
	}
	printf("\n");
	fclose(fp);
	return 0;
}