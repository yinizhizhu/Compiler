#include "stdafx.h"

void insertStr(Trie *root, const char *s)     //������s���뵽�ֵ�����
{
	if (root == NULL || *s == '\0')
		return;
	int i;
	Trie *p = root;
	while (*s != '\0')
	{
		if (p->next[*s - 'a'] == NULL)        //��������ڣ��������
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
	p->isStr = true;                       //���ʽ����ĵط���Ǵ˴����Թ���һ������
}

int searchStr(Trie *root, const char *s)  //����ĳ�������Ƿ��Ѿ�����
{
	Trie *p = root;
	while (p != NULL&&*s != '\0')
	{
		p = p->next[*s - 'a'];
		s++;
	}
	return (p != NULL&&p->isStr == true);      //�ڵ��ʽ������ı��Ϊtrueʱ�����ʲŴ���
}

void del(Trie *root)                      //�ͷ������ֵ���ռ�Ķ����ռ�
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