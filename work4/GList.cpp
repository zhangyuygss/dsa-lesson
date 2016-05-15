
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;
FILE *fp;


typedef struct GLNode
{
	char tag;
	union {
		char elem;
		struct GLNode *head;
	};
	struct GLNode *tail;
}GLNode ,*PGLNode;

void GList_Init(PGLNode *pgl);
void GList_Print(PGLNode pgl);
int GList_Dep(PGLNode pgl);

int main()
{
	int le;
	GLNode gl,*pgl=&gl;
	//fp = fopen("input.dat","r");
	GList_Init(&pgl);
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
	int maxl=0,dept=0;
	if(!pgl)return 1;
	if(pgl->tag == 0)
		return 0;
	for(PGLNode pp=pgl->head;pp;pp=pp->tail){
		dept = GList_Dep(pp);
		if(dept>maxl)maxl=dept;
	}
	return (maxl+1);
}

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

void GList_Init(PGLNode *pgl)
{
	char ch;
	scanf("%c",&ch);
	//fscanf(fp,"%c",&ch);
	if(ch == '('){//左括号，新建子表
		*pgl = (PGLNode)malloc(sizeof(GLNode));
		(*pgl)->tag = 1;//sublist
		GList_Init(&((*pgl)->head));
	}
	else {//左括号后只会出现左括号OR字母
		(*pgl) = (PGLNode)malloc(sizeof(GLNode));
		(*pgl)->tag = 0;//atom
		(*pgl)->elem = ch;
	}

	//fscanf(fp,"%c",&ch);
	scanf("%c",&ch);
	//字母后右括号，一层迭代完毕
	if(ch == ')')
		(*pgl)->tail = NULL;
	/*字母后出现逗号，继续向后构建*/
	if(ch == ',')
		GList_Init(&((*pgl)->tail));
}