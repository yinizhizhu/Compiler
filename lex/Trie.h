#pragma once
#if !defined TRIE_H
#define TRIE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "code.h"

#define NODE_LENGTH 26			//only support the lower string to store

typedef struct TrieNode                     //the node of Trie
{
	bool isStr;                            //tag the node is tail of the string
	struct TrieNode *next[NODE_LENGTH];            //the subTrie
} Trie;

Trie *initTrie(Trie *root);
void insertStr(Trie *root, const char *s);
bool searchStr(Trie *root, const char *s);
void del(Trie *root);

#endif