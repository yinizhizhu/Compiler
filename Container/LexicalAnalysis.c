#include "stdafx.h"

void handle()	//To get the upper and lower of key words
{
	FILE* fp = fopen("help.txt", "r");
	FILE* out = fopen("lowerContainer.txt", "w");

	char temp[N];
	int i, pos = 0;
	for (i = 1; i < 63; i++)
	{
		fscanf(fp, "#define %s %d\n", temp, &pos);
		stirngTolower(temp);
		fprintf(out, "\"%s\", ", temp);
	}

	fscanf(fp, "#define %s %d\n", temp, &pos);

	stirngTolower(temp);
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
	case '=':
	case '<':
	case '>':
	case '(':
	case ')':
	case ',':
	case '.':
	case ':':
	case ';':
	case '^':
	case '[':
	case ']':
	case 39:	//the char '\''
	case ' ':
	case '\n':
	case 9:
	case '\0':
		return true;
	default:
		return false;
		break;
	}
}

void output(int index, char temp, FILE* out)
{
	printf("(%s, %c)\n", KEY_WORDS[index], temp);
	fprintf(out, "(%s, %c)\n", KEY_WORDS[index], temp);
	return;
}

void readProgram(Trie* root)		//Read the program from source file.
{
	FILE* fp = fopen("program.txt", "r");
	FILE* out = fopen("Lexical.txt", "w");

	int move_next = 0, head, tail;
	int realGet, i, code=0;

	int lines = 1;		//The lines the cursor lands

	char buffer[2][BUFFER], token[N], temp;

	head = 0;
	tail = -1;
	while (true)
	{
		realGet = fread(buffer[move_next], 1, 2047, fp);
		buffer[move_next][realGet] = '\0';

		for (i = 0; i < realGet+1; i++)
		{
			tail++;
			temp = buffer[move_next][i];

			if (!isSeparator(temp))	//the next letter is not separator
			{
				//Go on moving to next and keep the letters into "token"
				if (isDigit(temp))		//The first letter is Digit, so just judge whether the "token" is a number or not
				{
					while (!isSeparator(temp))
					{
						token[tail - head] = temp;
						if (!isDigit(temp))
						{
							printf("Terrible name in %d line(s)! Please check.\n", lines);
							return;
						}
						i++;
						tail++;
						temp = buffer[move_next][i];
					}
					code = 37;
					i--;	//Step back( One Step )
					tail--;
				}
				else if (isAlpha(temp))		//The first is letter: ID or KEY_WORDS
				{
					while (!isSeparator(temp))
					{
						token[tail - head] = temp;
						if (code == 0 && isDigit(temp))
							code = 36;
						if (code == 0 && temp == '_')
							code = 36;
						if (!isDigit(temp) && !isAlpha(temp))
						{
							if (temp == '_')
								;
							else
							{
								printf("Terrible name in %d line(s)! Please check.\n", lines);
								return;
							}
						}
						i++;
						tail++;
						temp = buffer[move_next][i];
					}
					i--;
					tail--;
				}
				else
				{
					printf("Valid name in %d line(s)! Please check.\n", lines);
					return;
				}
			}
			else 	//the next letter is a separator
			{
				if (tail > head)
				{
					token[tail - head] = '\0';
					//printf("%s\n", token);
					if (code == 0)	//Token is not number or id
					{
						if (searchStr(root, token))		//key words
						{
							stringToupper(token);
							printf("(%s, )\n", token);
							fprintf(out, "(%s, )\n", token);
						}
						else	//identifier
						{
							if (strlen(token) > 0)
							{
								printf("(%s, %s)\n", KEY_WORDS[36], token);
								fprintf(out, "(%s, %s)\n", KEY_WORDS[36], token);
							}
						}
					}
					else	//integer
					{
						printf("(%s, %s)\n", KEY_WORDS[code], token);
						fprintf(out, "(%s, %s)\n", KEY_WORDS[code], token);
					}
				}
				switch (temp)
				{
				case '+':
					output(40, temp, out);
					break;
				case '-':
					output(41, temp, out);
					break;
				case '*':
					if (buffer[move_next][i + 1] == '*')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[60], temp, buffer[move_next][i + 1]);
						fprintf(out, "(%s£¬ %c%c)\n", KEY_WORDS[60], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(42, temp, out);
					break;

				case '/':
					output(43, temp, out);
					break;
				case '=':
					output(44, temp, out);
					break;
				case '<':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[47], temp, buffer[move_next][i + 1]);
						fprintf(out, "(%s£¬ %c%c)\n", KEY_WORDS[47], temp, buffer[move_next][i + 1]);
						i++;
					}
					else if (buffer[move_next][i + 1] == '>')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[49], temp, buffer[move_next][i + 1]);
						fprintf(out, "(%s£¬ %c%c)\n", KEY_WORDS[49], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(45, temp, out);
					break;

				case '>':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[48], temp, buffer[move_next][i + 1]);
						fprintf(out, "(%s£¬ %c%c)\n", KEY_WORDS[48], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(46, temp, out);
					break;

				case '(':
					output(50, temp, out);
					break;
				case ')':
					output(51, temp, out);
					break;
				case ',':
					output(52, temp, out);
					break;
				case '.':
					output(54, temp, out);
					break;
				case ':':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[57], temp, buffer[move_next][i + 1]);
						fprintf(out, "(%s£¬ %c%c)\n", KEY_WORDS[57], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(56, temp, out);
					break;

				case ';':
					output(58, temp, out);
					break;
				case '^':
					output(59, temp, out);
					break;
				case '[':
					output(61, temp, out);
					break;
				case ']':
					output(62, temp, out);
					break;
				case '\n':
					lines++;
					break;
				case 9:
					break;
				case 39:		//STRING: Just get the content between the two '\''.
					head = tail;
					i++;
					while (buffer[move_next][i] != 39)
					{ 
						token[tail - head] = buffer[move_next][i];
						i++;
						tail++;
						if (i >= realGet)
						{
							printf("The \"'\" cannot be matched in the %d line(s)!\n", lines);
							return;
						}
					}
					token[tail - head] = '\0';
					printf("(%s£¬ '%s')\n", KEY_WORDS[39], token);
					fprintf(out, "(%s£¬ '%s')\n", KEY_WORDS[39], token);
					break;
				default:
					break;
				}

				head = tail;
				tail = tail - 1;
				code = 0;
			}
		}
		if (realGet < 2047)
			break;

		move_next = (move_next + 1) % 2;
	}
	fclose(out);
	fclose(fp);
	return;
}

int main()
{
	Trie *root = NULL;
	root = initTrie(root);	//Trie has stpred the key words
	initSymbolList();	//Initial the symbol list
	readProgram(root);
	delSymbolList();
	del(root);
	return 0;
}