#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAX 26

using namespace std;

typedef struct TrieNode                     //Trie�������
{
    bool isStr;                            //��Ǹý�㴦�Ƿ񹹳ɵ���
    struct TrieNode *next[MAX];            //���ӷ�֧
} Trie;

void insertStr(Trie *root,const char *s)     //������s���뵽�ֵ�����
{
    if(root==NULL||*s=='\0')
        return;
    int i;
    Trie *p=root;
    while(*s!='\0')
    {
        if(p->next[*s-'a']==NULL)        //��������ڣ��������
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
    p->isStr=true;                       //���ʽ����ĵط���Ǵ˴����Թ���һ������
}

int searchStr(Trie *root,const char *s)  //����ĳ�������Ƿ��Ѿ�����
{
    Trie *p=root;
    while(p!=NULL&&*s!='\0')
    {
        p=p->next[*s-'a'];
        s++;
    }
    return (p!=NULL&&p->isStr==true);      //�ڵ��ʽ������ı��Ϊtrueʱ�����ʲŴ���
}

void del(Trie *root)                      //�ͷ������ֵ���ռ�Ķ����ռ�
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
    int n,m;                              //nΪ����Trie������ĵ�������mΪҪ���ҵĵ�����
    char s[100];
    Trie *root= (Trie *)malloc(sizeof(Trie));
    for(i=0; i<MAX; i++)
    {
        root->next[i]=NULL;
    }
    root->isStr=false;
    scanf("%d",&n);
    getchar();
    for(i=0; i<n; i++)               //�Ƚ����ֵ���
    {
        scanf("%s",s);
        insertStr(root,s);
    }
    scanf("%d",&m);
    for(i=0; i<m; i++)               //����
    {
        scanf("%s",s);
        if(searchStr(root,s)==1)
            printf("YES\n");
        else
            printf("NO\n");
    }
    printf("\n");
    del(root);                         //�ͷſռ����Ҫ
    return 0;
}
