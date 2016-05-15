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

char Priorit_Juge(char c1,char c2);
void Exchange();


int main()
{
	Exchange();
	cout<<endl;
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


char Priorit_Juge(char c1,char c2)
{
	if(c1 == '+'){
		switch(c2){
			case '+':return '>';
			case '-':return '>';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	if(c1 == '-'){
		switch(c2){
			case '+':return '>';
			case '-':return '>';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	if(c1 == '*'){
		switch(c2){
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	if(c1 == '/'){
		switch(c2){
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			case '(':return '<';
			case ')':return '>';
			case '#':return '>';
		}
	}
	if(c1 == '('){
		switch(c2){
			case '+':return '<';
			case '-':return '<';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			case ')':return '=';
			//case '#':return 'k';
		}
	}
	if(c1 == ')'){
		switch(c2){
			case '+':return '>';
			case '-':return '>';
			case '*':return '>';
			case '/':return '>';
			//case '(':return 'k';
			case ')':return '>';
			case '#':return '>';
		}
	}
	if(c1 == '#'){
		switch(c2){
			case '+':return '<';
			case '-':return '<';
			case '*':return '<';
			case '/':return '<';
			case '(':return '<';
			//case ')':return 'k';
			case '#':return '=';
		}
	}
}

void Exchange()
{
	char ch,chs[50];
	gets(chs);
	int k=strlen(chs);
	Linked_Stack lstack,*plstack=&lstack;
	Stack_Init(&plstack);
	Push(plstack,'#');//规范输入，给表达式前后加上#
	chs[k]='#';
	chs[k+1]='\0';
	for(int i=0;i<k+1;i++){
		ch = chs[i];
		if(ch>96 && ch<123){
			cout<<ch;
		}
		else{
			if(Is_Empty(plstack))Push(plstack,ch);
			else{
				char ch2=Get_top(plstack);
				if(Priorit_Juge(ch2,ch) == '<')Push(plstack,ch);
				else if(Priorit_Juge(ch2,ch) == '>'){
					cout<<ch2;
					Pop(plstack);
					i--;//继续判断栈顶
				}
				else if(Priorit_Juge(ch2,ch) == '=')Pop(plstack);
			}
		}
	}
}