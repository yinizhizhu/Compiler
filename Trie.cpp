#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAX 26

using namespace std;

typedef struct TrieNode                     //Trie结点声明
{
    bool isStr;                            //标记该结点处是否构成单词
    struct TrieNode *next[MAX];            //儿子分支
} Trie;

void insertStr(Trie *root,const char *s)     //将单词s插入到字典树中
{
    if(root==NULL||*s=='\0')
        return;
    int i;
    Trie *p=root;
    while(*s!='\0')
    {
        if(p->next[*s-'a']==NULL)        //如果不存在，则建立结点
        {
            Trie *temp=(Trie *)malloc(sizeof(Trie));
            for(i=0; i<MAX; i++)
            {
                temp->next[i]=NULL;
            }
            temp->isStr=false;
            p->next[*s-'a']=temp;
            p=p->next[*s-'a'];
        }
        else
        {
            p=p->next[*s-'a'];
        }
        s++;
    }
    p->isStr=true;                       //单词结束的地方标记此处可以构成一个单词
}

int searchStr(Trie *root,const char *s)  //查找某个单词是否已经存在
{
    Trie *p=root;
    while(p!=NULL&&*s!='\0')
    {
        p=p->next[*s-'a'];
        s++;
    }
    return (p!=NULL&&p->isStr==true);      //在单词结束处的标记为true时，单词才存在
}

void del(Trie *root)                      //释放整个字典树占的堆区空间
{
    int i;
    for(i=0; i<MAX; i++)
    {
        if(root->next[i]!=NULL)
        {
            del(root->next[i]);
        }
    }
    free(root);
}

int main(int argc, char *argv[])
{
    int i;
    int n,m;                              //n为建立Trie树输入的单词数，m为要查找的单词数
    char s[100];
    Trie *root= (Trie *)malloc(sizeof(Trie));
    for(i=0; i<MAX; i++)
    {
        root->next[i]=NULL;
    }
    root->isStr=false;
    scanf("%d",&n);
    getchar();
    for(i=0; i<n; i++)               //先建立字典树
    {
        scanf("%s",s);
        insertStr(root,s);
    }
    scanf("%d",&m);
    for(i=0; i<m; i++)               //查找
    {
        scanf("%s",s);
        if(searchStr(root,s)==1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    printf("\n");
    del(root);                         //释放空间很重要
    return 0;
}
