#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;
char *emp="()";

typedef enum{ATOM,LIST}ElemTag;
typedef struct GLNode
{
	char tag;
	union {
		char elem;
		struct {struct GLNode *hp,*tp;}ptr;
	};
}GLNode ,*PGLNode;

void GList_Init(PGLNode *pgl,char *ss);
void GList_Print(PGLNode pgl);
int GList_Dep(PGLNode pgl);
void sever(char *sub,char *hsub);
void SubString(char *sub,char *ss,int pos,int len);
int main()
{
	int le;
	//FILE *fp;
	GLNode gl,*pgl=&gl;
	//fp = fopen("input.dat","r");
	char str[100];
	gets(str);
	//fscanf(fp,"%s",str);
	int i=0;
	while(str[i]!='\0')//处理不规范输入
	{
		if(str[i]==')' && isalpha(str[i+1])){
			int temp=strlen(str);
			for(int j=temp;j>i+1;j--)str[j]=str[j-1];
			str[i+1]=',';
			str[temp+1]='\0';
		}
		i++;
	}
	GList_Init(&pgl,str);
	le=GList_Dep(pgl);
	cout<<le<<endl;
	cout<<le<<endl;
	//GList_Print(pgl);
	//fclose (fp);
	//getchar();
	//getchar();
	return 0;
}

int GList_Dep(PGLNode pgl)
{
	int dept=0,maxl=0;
	if(!pgl)
		return 1;
	if(pgl->tag == ATOM)
		return 0;
	for(PGLNode pp=pgl;pp;pp=pp->ptr.tp){
		dept = GList_Dep(pp->ptr.hp);
		if(dept>maxl)maxl=dept;
	}
	return (maxl+1);
}
/*
void GList_Print(PGLNode pgl)
{
	if(pgl->tag == 1){
		cout<<'(';
		GList_Print(pgl->head);
		cout<<')';
	}
	else cout<<pgl->elem;
	if (pgl->tail != NULL){
		cout<<',';
		GList_Print(pgl->tail);
	}
}
*/
void GList_Init(PGLNode *pgl,char *ss)
{
	if(!(strcmp(ss,emp)))(*pgl)=NULL;
	else{
		(*pgl) = (PGLNode)malloc(sizeof(GLNode));
		if(strlen(ss)==1){
			(*pgl)->tag = ATOM;
			(*pgl)->elem = ss[0];
		}
		else{
			(*pgl)->tag = LIST;
			PGLNode p=(*pgl);
			char sub[100];
			SubString(sub,ss,1,strlen(ss)-2);
			PGLNode q;
			do{
				char hsub[100];
				sever(sub,hsub);
				GList_Init(&(p->ptr.hp) , hsub);
				q=p;
				if(sub[0]!='\0'){
					p = (PGLNode)malloc(sizeof(GLNode));
					p->tag = LIST;
					q->ptr.tp = p;
				}
			}while(sub[0]!='\0');
			q->ptr.tp = NULL;
		}
	}
}

void SubString(char *sub,char *ss,int pos,int len)
{
	for (int i = 0; i < len; ++i)
	{
		sub[i] = ss[pos++];
	}
	sub[len] = '\0';
}

void sever(char *sub,char *hsub)
{
	int i=0,k=0,n=strlen(sub);
	int temp=0;
	for(i=0;i<n;i++){
		if(sub[i] == '(')temp++;
		else if(sub[i] == ')')temp--;
		if(sub[i] == ',' && !temp)break;
	}
	if(i<n-1){
		SubString(hsub,sub,0,i);
		SubString(sub,sub,i+1,n-i-1);
	}
	else{
		SubString(hsub,sub,0,n);
		sub[0] = '\0';
	}
}