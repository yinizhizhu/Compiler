#include "stdafx.h"
#include "Trie.cpp"

const int N = 100;

extern void stirng_tolower(char *arr);
extern void insertStr(Trie *root, const char *s);
extern int searchStr(Trie *root, const char *s);
extern void del(Trie *root);
extern void init_Trie(Trie *root);


void handle()	//To get the upper and lower of key words
{
	FILE* fp = fopen("help.txt", "r");
	FILE* out = fopen("lowerContainer.txt", "w");
	char temp[N];
	int i, pos = 0;
	for (i = 1; i < 63; i++)
	{
		fscanf(fp, "#define %s %d\n", temp, &pos);
		stirng_tolower(temp);
		fprintf(out, "\"%s\", ", temp);
	}
	fscanf(fp, "#define %s %d\n", temp, &pos);
	stirng_tolower(temp);
	fprintf(out, "\"%s\"\n", temp);
	fclose(out);
	fclose(fp);
	return;
}

bool isSeparator(char getChar)	//return "true" while separator
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

void readProgram()		//Read the program from source file.
{
	FILE* fp = fopen("program.txt", "r");
	char temp[N];
	char getChar;
	int pos = 0;
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
	Trie *root=NULL;
	init_Trie(root);	//Trie has stpred the key words
	del(root);
	return 0;
}