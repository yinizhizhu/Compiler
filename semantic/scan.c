#include "scan.h"

char *keyword[KEYWORDSUM] = { "if", "else", "for", "while", "do", "int", "read", "write" };
char singleword[50] = "+-*(){};,:";//The single sepqrator

char doubleword[10] = "><=!";//The double separators
char Scanin[300] = "source.txt";
char Scanout[300] = "syntaxResult.txt";
FILE *fin, *fout;

int lex()//Lex analysisor
{
	char ch, token[40];
	int es = 0, j; //Error code: es == 0, which means no error.
	printf("The file of source code is: %s\n", Scanin);
	printf("The file of storing the result of Lexing: %s\n", Scanout);
	if ((fin = fopen(Scanin, "r")) == NULL)
	{
		printf("\nCannot open the file \"%s\"!\n", Scanin);
		return 1;
	}
	if ((fout = fopen(Scanout, "w")) == NULL)
	{
		printf("\nCannot create the file \"%s\"!\n", Scanout);
		return 2;
	}
	ch = getc(fin);
	while (ch != EOF)
	{
		while (ch == ' ' || ch == '\n' || ch == '\t')
			ch = getc(fin);
		if (isalpha(ch))//Identifier
		{
			token[0] = ch;
			j = 1;
			ch = getc(fin);
			while (isalnum(ch))
			{
				token[j++] = ch;
				ch = getc(fin);
			}
			token[j] = '\0';

			if (isKeyWords(token))
				fprintf(fout, "%s\t%s\n", token, token);  //output the KeyWord
			else
				fprintf(fout, "%s\t%s\n", "ID", token);  //output the Identifier
		}
		else if (isdigit(ch))//Number
		{
			token[0] = ch;
			j = 1;
			ch = getc(fin);
			while (isdigit(ch))
			{
				token[j++] = ch;
				ch = getc(fin);
			}
			token[j] = '\0';
			fprintf(fout, "%s\t%s\n", "NUM", token);  //output the Number
		}
		else if (strchr(singleword, ch)>0)  //The single separator
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			fprintf(fout, "%s\t%s\n", token, token);  //output the separator
		}
		else if (strchr(doubleword, ch)>0)  //The double separators
		{
			token[0] = ch;
			ch = getc(fin);
			if (ch == '=')
			{
				token[1] = ch;
				token[2] = '\0';
				ch = getc(fin);
			}
			else//For '='
				token[1] = '\0';
			fprintf(fout, "%s\t%s\n", token, token);  //output the separator(s)
		}
		else if (ch == '/')  //Handle with the comment
		{
			ch = getc(fin);
			if (ch == '*') //For '/*'
			{
				char ch1;
				ch1 = getc(fin);
				do
				{
					ch = ch1; ch1 = getc(fin);
				} while ((ch != '*' || ch1 != '/') && ch1 != EOF);
				ch = getc(fin);
			}
			else  //For '//'
			{
				token[0] = '/'; token[1] = '\0';
				fprintf(fout, "%s\t%s\n", token, token);  //output the '/'
			}
		}
		else//Deal with the Error
		{
			token[0] = ch;
			token[1] = '\0';
			ch = getc(fin);
			es = 3;
			fprintf(fout, "%s\t%s\n", "ERROR", token);  //output the Code of Errof
		}
	}
	fclose(fin);
	fclose(fout);
	return es;
}

bool isKeyWords(const char *token)
{
	int i = 0;
	for (; i < KEYWORDSUM; i++)
		if (strcmp(token, keyword[i]) == 0)
			return true;
	return false;
}