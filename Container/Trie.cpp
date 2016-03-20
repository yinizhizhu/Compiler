#include "stdafx.h"

void insertStr(Trie *root, const char *s)     //将单词s插入到字典树中
{
	if (root == NULL || *s == '\0')
		return;
	int i;
	Trie *p = root;
	while (*s != '\0')
	{
		if (p->next[*s - 'a'] == NULL)        //如果不存在，则建立结点
		{
			Trie *temp = (Trie *)malloc(sizeof(Trie));
			for (i = 0; i<NODE_LENGTH; i++)
			{
				temp->next[i] = NULL;
			}
			temp->isStr = false;
			p->next[*s - 'a'] = temp;
			p = p->next[*s - 'a'];
		}
		else
		{
			p = p->next[*s - 'a'];
		}
		s++;
	}
	p->isStr = true;                       //单词结束的地方标记此处可以构成一个单词
}

int searchStr(Trie *root, const char *s)  //查找某个单词是否已经存在
{
	Trie *p = root;
	while (p != NULL&&*s != '\0')
	{
		p = p->next[*s - 'a'];
		s++;
	}
	return (p != NULL&&p->isStr == true);      //在单词结束处的标记为true时，单词才存在
}

void del(Trie *root)                      //释放整个字典树占的堆区空间
{
	int i;
	if (root == NULL)
		return;
	for (i = 0; i<NODE_LENGTH; i++)
		if (root->next[i] != NULL)
			del(root->next[i]);
	free(root);
}

void init_Trie(Trie *root)	//Init the Trie to store the Key Words
{
	int i;
	root = (Trie *)malloc(sizeof(Trie));
	for (i = 0; i<NODE_LENGTH; i++)
		root->next[i] = NULL;
	root->isStr = false;
	for (i = 0; i < 35; i++)
		insertStr(root, key_words[i]);
	return;
}