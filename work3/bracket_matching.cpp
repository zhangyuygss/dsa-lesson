#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

typedef struct Stack_Node
{
	char dat;
	struct Stack_Node *next;
}Stack_Node,*PStack_Node;

typedef struct Linked_Stack
{
	PStack_Node top;
	//PStack_Node bottom;
}Linked_Stack,*PLinked_Stack;

int Stack_Init(PLinked_Stack *pstack);
int Is_Empty(PLinked_Stack pstack);
char Pop(PLinked_Stack pstack);
char Get_top(PLinked_Stack pstack);
int Push(PLinked_Stack pstack,char date);
int Stack_Print(PLinked_Stack pstack);
int Is_matched(PLinked_Stack plstack, char *a,int n);



int main()
{
	Linked_Stack lstack,*plstack = &lstack;
	char brackets[110];
	gets(brackets);
	int n=strlen(brackets);
	if(!Stack_Init(&plstack))return 2;
	Is_matched(plstack,brackets,n);
	return 0;
}

int Stack_Init(PLinked_Stack *ppstack)
{
	*ppstack = (PLinked_Stack)malloc(sizeof(Linked_Stack));
	if(*ppstack){
		(*ppstack)->top=NULL;
		return 1;
	}
	cout<<"No Space for Init!"<<endl;
	return 0;
}

int Is_Empty(PLinked_Stack pstack)
{//return 1 if stack is empty
	if(pstack->top == NULL)
		return 1;
	return 0;
}


char Pop(PLinked_Stack pstack)
{//return top elem of the stack and delet it
	PStack_Node p=pstack->top;
	char k=p->dat;
	pstack->top=p->next;
	free(p);
	return k;
}

char Get_top(PLinked_Stack pstack)
{
	return pstack->top->dat;
}

int Push(PLinked_Stack pstack,char date)
{
	PStack_Node pnode;
	pnode=(PStack_Node)malloc(sizeof(Stack_Node));
	if(!pnode){
		cout<<"No Space for Push!"<<endl;
		return 0;
	}
	pnode->dat = date;
	pnode->next = (pstack)->top;
	(pstack)->top = pnode;
	return 1;
}

int Stack_Print(PLinked_Stack pstack)
{
	PStack_Node pnode = pstack->top;
	while(pnode){
		cout<<pnode->dat<<endl;
		pnode = pnode->next;
	}
	return 1;
}

int Is_matched(PLinked_Stack plstack, char *a,int n)
{
	for(int i=0;i<n;i++){
		if(a[i]=='(' || a[i]=='{' || a[i]=='['){
			Push(plstack,a[i]);
		}
		if(a[i]==')' || a[i]=='}' || a[i]==']'){
			if(!Is_Empty(plstack)){
				char temp=Get_top(plstack);
				if(temp == '{' && a[i]== '}' 
					|| temp=='[' && a[i]==']'
					|| temp=='(' && a[i]==')')
					Pop(plstack);
				else{
					cout<<"No"<<endl;
					return 0;
				}
			}
			else{
				cout<<"No"<<endl;
				return 0;
			}
		}
	}
	if(Is_Empty(plstack)){
		cout<<"Yes"<<endl;
		return 1;
	}
	else{
		cout<<"No"<<endl;
		return 0;
	}
}
