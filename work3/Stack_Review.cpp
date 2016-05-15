#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

typedef struct LStackNode
{
	char elem;
	struct LStackNode *next;
}LStackNode,*PLStackNode;

typedef struct LStack
{
	PLStackNode top;
	PLStackNode base;
}LStack,*PLStack;

int LStack_Init(PLStack *ppls);
int LStack_Push(PLStack pls,char ch);
int LStack_Pop(PLStack pls);
int LStack_Isempty(LStack ls);
char LStack_Gettop(LStack ls);

void Dec_2_Oct(int num,PLStack pls);
int Bracket_Matching(char *s);

char Priority_Judge(char ch1,char ch2);
void Express_Change(char *str);

int main()
{
	PLStack pls;
	LStack_Init(&pls);
	char str[100];
	gets(str);
	if(Bracket_Matching(str))
		cout<<"Matched!"<<endl;
	else cout<<"Not Matched!"<<endl;
	getchar();
	getchar();
	return 0;
}

void Express_Change(char *str)
{
	
}


char Priority_Judge(char ch1,char ch2)
{
	switch(ch1){
		case '+':
			switch(ch2){
				case '+':return '>';
				case '-':return '>';
				case '*':return '<';
				case '/':return '<';
				case '(':return '<';
				case ')':return '>';
				case '#':return '>';
			}
		case '-':
			switch(ch2){
				case '+':return '>';
				case '-':return '>';
				case '*':return '<';
				case '/':return '<';
				case '(':return '<';
				case ')':return '>';
				case '#':return '>';
			}
		case '*':
			switch(ch2){
				case '+':return '>';
				case '-':return '>';
				case '*':return '>';
				case '/':return '>';
				case '(':return '<';
				case ')':return '>';
				case '#':return '>';
			}
		case '/':
			switch(ch2){
				case '+':return '>';
				case '-':return '>';
				case '*':return '>';
				case '/':return '>';
				case '(':return '<';
				case ')':return '>';
				case '#':return '>';
			}
		case '(':
			switch(ch2){
				case '+':return '<';
				case '-':return '<';
				case '*':return '<';
				case '/':return '<';
				case '(':return '<';
				case ')':return '=';
				case '#':cout<<"error";break;
			}
		case '#':
			switch(ch2){
				case '+':return '<';
				case '-':return '<';
				case '*':return '<';
				case '/':return '<';
				case '(':return '<';
				case ')':cout<<"error";break;
				case '#':return '=';
			}
	}
}


int Bracket_Matching(char *s)
{
	PLStack pls;
	LStack_Init(&pls);
	for (int i = 0; s[i]!='\0'; ++i)
	{
		if(s[i]=='(' || s[i]=='[' || s[i]=='{')
			LStack_Push(pls,s[i]);
		else{
			char topchar = LStack_Gettop(*pls);
			if(s[i] - topchar ==2 || s[i] - topchar ==1)//关系见asc码表
				LStack_Pop(pls);
			else
				return 0;
		}
	}
	return LStack_Isempty(*pls);
}

int LStack_Init(PLStack *ppls)
{
	(*ppls) = (PLStack)malloc(sizeof(LStack));
	if((*ppls)){
		(*ppls)->base = (PLStackNode)malloc(sizeof(LStackNode));
		(*ppls)->base->next = NULL;
		(*ppls)->top = (*ppls)->base;
		return 1;
	}
	else return 0;
}

int LStack_Push(PLStack pls,char ch)
{
	PLStackNode pnode;
	pnode = (PLStackNode)malloc(sizeof(LStackNode));
	if(pnode){
		pnode->elem = ch;
		pnode->next = pls->top;
		pls->top = pnode;
		return 1;
	}
	else return 0;
}

int LStack_Pop(PLStack pls)
{
	if(pls->top == pls->base)return 0;
	else{
		PLStackNode ptemp=pls->top;
		pls->top = pls->top->next;
		free(ptemp);
		return 1;
	}
}

int LStack_Isempty(LStack ls)
{
	return ls.top == ls.base;
}

char LStack_Gettop(LStack ls)
{
	return ls.top->elem;
}

void Dec_2_Oct(int num,PLStack pls)
{
	int m;//num为商，m为余数
	while(num){
		m = num%8;
		num/=8;
		LStack_Push(pls,m+'0');
	}
	while(!LStack_Isempty(*pls)){
		cout<<LStack_Gettop(*pls);
		LStack_Pop(pls);
	}
}
