#include "LexicalAnalysis.h"

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
"DIGSEQ", "REALNUMBER", "CHARACTER_STRING", "PLUS",
"MINUS", "STAR", "SLASH", "EQUAL",
"LT", "GT", "LE", "GE",
"NOTEQUAL", "LPAREN", "RPAREN", "COMMA",
"P_MARK", "DOT", "DOTDOT", "COLON",
"ASSIGNMENT", "SEMICOLON", "UPARROW", "STARSTAR",
"LBRAC", "RBRAC", "Q_MARK" };


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
	fprintf(out, "%s\n", KEY_WORDS[index], temp);
	//fprintf(out, "(%s, %c)\n", KEY_WORDS[index], temp);
	return;
}

void readProgram()		//Read the program from source file.
{
	FILE* fp = fopen("sample.txt", "r");
	FILE* out = fopen("inputSyn.txt", "w");

	int move_next = 0, head, tail;
	int realGet, i, code=0;

	int lines = 1, index, tag = 0;		//The lines the cursor lands

	char buffer[2][BUFFER], word[N], temp;

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
				//Go on moving to next and keep the letters into "word"
				if (isDigit(temp))		//The first letter is Digit, so just judge whether the "word" is a number or not
				{
					while (!isSeparator(temp))
					{
						word[tail - head] = temp;
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
						word[tail - head] = temp;
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
					word[tail - head] = '\0';
					//printf("%s\n", word);
					if (code == 0)	//word is not number or id
					{
						index = searchStr(word);
						if (index > 0)		//key words
						{
							printf("(%s, )\n", KEY_WORDS[index]);
							fprintf(out, "%s\n", KEY_WORDS[index]);
							//fprintf(out, "(%s, )\n", word);
							if (tag)
								pushQueue(word);	//for semantic
							else
							{
								if (strcmp(word, "begin") == 0)
									tag = 1;
							}
						}
						else	//identifier
						{
							if (strlen(word) > 0)
							{
								if (!insertIntoSymbolList(word))
									printf("Error, cannot insert!\n");	//insert the word into the symbol list
								printf("(%s, %s)\n", KEY_WORDS[36], word);
								fprintf(out, "%s\n", KEY_WORDS[36], word);
								//fprintf(out, "(%s, %s)\n", KEY_WORDS[36], word);
								if (tag)
									pushQueue(word);	//for semantic
							}
						}
					}
					else	//integer
					{
						if (!insertIntoSymbolList2(word, 4, 0, 0))
							printf("Error, cannot insert2!\n");	//insert the constant into the symbol list
						printf("(%s, %s)\n", KEY_WORDS[code], word);
						fprintf(out, "%s\n", KEY_WORDS[code], word);
						//fprintf(out, "(%s, %s)\n", KEY_WORDS[code], word);
						if (tag)
							pushQueue(word);	//for semantic
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
						printf("(%s�� %c%c)\n", KEY_WORDS[60], temp, buffer[move_next][i + 1]);
						fprintf(out, "%s\n", KEY_WORDS[60], temp, buffer[move_next][i + 1]);
						//fprintf(out, "(%s�� %c%c)\n", KEY_WORDS[60], temp, buffer[move_next][i + 1]);
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
						printf("(%s�� %c%c)\n", KEY_WORDS[47], temp, buffer[move_next][i + 1]);
						fprintf(out, "%s\n", KEY_WORDS[47], temp, buffer[move_next][i + 1]);
						//fprintf(out, "(%s�� %c%c)\n", KEY_WORDS[47], temp, buffer[move_next][i + 1]);
						i++;
					}
					else if (buffer[move_next][i + 1] == '>')
					{
						printf("(%s�� %c%c)\n", KEY_WORDS[49], temp, buffer[move_next][i + 1]);
						fprintf(out, "%s\n", KEY_WORDS[49], temp, buffer[move_next][i + 1]);
						//fprintf(out, "(%s�� %c%c)\n", KEY_WORDS[49], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(45, temp, out);
					break;

				case '>':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s�� %c%c)\n", KEY_WORDS[48], temp, buffer[move_next][i + 1]);
						fprintf(out, "%s\n", KEY_WORDS[48], temp, buffer[move_next][i + 1]);
						//fprintf(out, "(%s�� %c%c)\n", KEY_WORDS[48], temp, buffer[move_next][i + 1]);
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
						printf("(%s�� %c%c)\n", KEY_WORDS[57], temp, buffer[move_next][i + 1]);
						fprintf(out, "%s\n", KEY_WORDS[57], temp, buffer[move_next][i + 1]);
						//fprintf(out, "(%s�� %c%c)\n", KEY_WORDS[57], temp, buffer[move_next][i + 1]);
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
						word[tail - head] = buffer[move_next][i];
						i++;
						tail++;
						if (i >= realGet)
						{
							printf("The \"'\" cannot be matched in the %d line(s)!\n", lines);
							return;
						}
					}
					word[tail - head] = '\0';
					if (!insertIntoSymbolList2(word, 1, 3, 0))
						printf("Error, cannot insert2!\n");
					printf("(%s�� '%s')\n", KEY_WORDS[39], word);
					fprintf(out, "%s\n", KEY_WORDS[39], word);
					//fprintf(out, "(%s�� '%s')\n", KEY_WORDS[39], word);
					if (tag)
						pushQueue(word);	//for semantic
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

int lex()
{
	if (initSymbolList())	//Initial the symbol list
	{
		readProgram();
		//showSymbolList();
	}
	else
	{
		printf("Error in initialing!\n");
		return -1;
	}
	//delSymbolList();
	return 0;
}