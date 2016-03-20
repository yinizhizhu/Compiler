#include "stdafx.h"
#include "Trie.cpp"

const int N = 30;
const int BUFFER = 2048;

extern void stirng_tolower(char *arr);
extern void string_toupper(char *arr);
extern void insertStr(Trie *root, const char *s);
extern int searchStr(Trie *root, const char *s);
extern void del(Trie *root);
extern Trie *init_Trie(Trie *root);


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
	case '\'':
	case ' ':
	case '\n':
		return true;
	default:
		return false;
		break;
	}
}

void output(int index, char temp)
{
	printf("(%s, %c)\n", KEY_WORDS[index], temp);
	return;
}

void readProgram(Trie* root)		//Read the program from source file.
{
	FILE* fp = fopen("program.txt", "r");

	int move_next = 0, head, tail;
	int realGet, i;

	char buffer[2][BUFFER], token[N], temp;

	head = 0;
	tail = -1;
	while (true)
	{
		realGet = fread(buffer[move_next], 1, 2047, fp);
		buffer[move_next][realGet] = '\0';

		for (i = 0; i < realGet; i++)
		{
			tail++;
			temp = buffer[move_next][i];
			if (isSeparator(temp))	//the next letter is a separator
			{
				token[tail - head] = '\0';
				//printf("%s\n", token);
				if (token[0] >= 'a' && token[0] <= 'z')	//the first one is a letter, so it's a string
				{
					if (searchStr(root, token))		//key words
					{
						string_toupper(token);
						printf("(%s, )\n", token);
					}
					else
						printf("(%s, %s)\n", KEY_WORDS[36], token);
				}
				else if (token[0] >= '0' && token[0] <= '9')	//token is a number
					printf("(%s, %s)\n", KEY_WORDS[37], token);
				else
					;

				switch (temp)
				{
				case '+':
					output(40, temp);
					break;
				case '-':
					output(41, temp);
					break;
				case '*':
					if (buffer[move_next][i + 1] == '*')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[60], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(42, temp);
					break;

				case '/':
					output(43, temp);
					break;
				case '=':
					output(44, temp);
					break;
				case '<':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[47], temp, buffer[move_next][i + 1]);
						i++;
					}
					else if (buffer[move_next][i + 1] == '>')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[49], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(45, temp);
					break;

				case '>':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[48], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(46, temp);
					break;

				case '(':
					output(50, temp);
					break;
				case ')':
					output(51, temp);
					break;
				case ',':
					output(52, temp);
					break;
				case '.':
					output(54, temp);
					break;
				case ':':
					if (buffer[move_next][i + 1] == '=')
					{
						printf("(%s£¬ %c%c)\n", KEY_WORDS[57], temp, buffer[move_next][i + 1]);
						i++;
					}
					else
						output(56, temp);
					break;

				case ';':
					output(58, temp);
					break;
				case '^':
					output(59, temp);
					break;
				case '[':
					output(61, temp);
					break;
				case ']':
					output(62, temp);
					break;
				default:
					break;
				}

				head = tail;
				tail = tail - 1;
			}
			else if (temp == 9)
			{
				head = tail;
				tail = tail - 1;
			}
			else	//the next letter is not separator, go on moving to next and keep the letter into "token"
			{
				token[tail - head] = temp;
				//printf("\n head = %d, tail = %d, char=%c\n", head, tail, temp);
			}
		}

		if (realGet < 2047)
			break;

		move_next = (move_next + 1) % 2;
	}
	fclose(fp);
	return;
}

int main()
{
	Trie *root = NULL;
	root = init_Trie(root);	//Trie has stpred the key words
	readProgram(root);
	//for (i = 0; i < 35; i++)
	//	if (searchStr(root, key_words[i]))
	//		printf("%s\n", key_words[i]);
	del(root);
	return 0;
}