#include "Trie.h"

const char key_words[ALL_KEY][TYPE_LENGTH] = {
"and", "array", "pbegin", "case",
"const", "div", "do", "downto",
"else", "end", "pfile", "for",
"function", "goto", "if", "in",
"label", "mod", "nil", "not",
"of", "or", "packed", "procedure",
"program", "record", "repeat", "set",
"then", "to", "type", "until",
"var", "while", "with", "identifier",
"int", "realnumber", "character_string", "plus",
"minus", "star", "slash", "equal",
"lt", "gt", "le", "ge", "notequal",
"lparen", "rparen", "comma",
"p_mark", "dot", "dotdot", "colon",
"assignment", "semicolon", "uparrow", "starstar",
"lbrac", "rbrac", "q_mark", "integer",
"word" };

Trie *initTrie(Trie *root)	//Init the Trie to store the Key Words
{
	int i;
	root = (Trie *)malloc(sizeof(Trie));
	for (i = 0; i<NODE_LENGTH; i++)
		root->next[i] = NULL;
	root->isStr = false;
	for (i = 0; i < 35; i++)
		insertStr(root, key_words[i]);
	insertStr(root, key_words[63]);
	insertStr(root, key_words[64]);
	return root;
}

void insertStr(Trie *root, const char *s)     //insert the string into the trie tree
{
	if (root == NULL || *s == '\0')
		return;
	int i;
	Trie *p = root;
	while (*s != '\0')
	{
		if (p->next[*s - 'a'] == NULL)        //if not, we create
		{
			Trie *temp = (Trie *)malloc(sizeof(Trie));
			for (i = 0; i<NODE_LENGTH; i++)
				temp->next[i] = NULL;
			temp->isStr = false;
			p->next[*s - 'a'] = temp;
			p = p->next[*s - 'a'];
		}
		else
			p = p->next[*s - 'a'];
		s++;
	}
	p->isStr = true;                       //here is the string
}

bool searchStr(Trie *root, const char *s)  //searcht the string
{
	Trie *p = root;
	while (p != NULL&&*s != '\0')
	{
		p = p->next[*s - 'a'];
		s++;
	}
	return (p != NULL&&p->isStr == true);      //return true while there is
}

void del(Trie *root)                      //free the room
{
	int i;
	if (root == NULL)
		return;
	for (i = 0; i<NODE_LENGTH; i++)
		if (root->next[i] != NULL)
			del(root->next[i]);
	free(root);
}
