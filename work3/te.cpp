#include <stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node
{
    char data;
    struct node *next;
} node,*Pnode;

typedef struct stacklink
{
    Pnode top;
} stacklink,*Pstack;

void Push(Pstack L,char a)
{
    Pnode p;
    p=(Pnode)malloc(sizeof(node));
    p->data=a;
    p->next=L->top;
    L->top=p;
}

char topelem(Pstack L)
{
    Pnode p;
    p=(Pnode)malloc(sizeof(node));
    char a;
    p=L->top;
    a=p->data;
    return a;
}

void Pop(Pstack L)
{
    L->top=L->top->next;
}

int main()
{
    Pstack L;
    L=(Pstack)malloc(sizeof(stacklink));
    L->top=NULL;
    char str[100];
    scanf("%s",str);
    int n,i;
    n=strlen(str);
    for(i=0; i<n; i++)
    {
        if(str[i]=='('||str[i]=='['||str[i]=='{')
        {
            Push(L,str[i]);
        }
        else if(str[i]==')')
        {
            if(topelem(L)=='(')
            {
                Pop(L);
            }
            else
            {
                printf("No\n");
                break;
            }
        }
        else if(str[i]==']')
        {
            if(topelem(L)=='[')
            {
                Pop(L);
            }
            else
            {
                printf("No\n");
                break;
            }
        }
        else if(str[i]=='}')
        {
            if(topelem(L)=='{')
            {
                Pop(L);
            }
            else
            {
                printf("No\n");
                break;
            }
        }
    }
    if(L->top==NULL)printf("Yes\n");
    if(i==n)
    {
        if(L->top!=NULL)printf("No\n");
    }
    return 0;
}