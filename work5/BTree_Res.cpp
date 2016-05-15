/*由先序和中序表式求后序*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#define MAXSIZE 110
using namespace std;


typedef struct BTNode{
	char elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

int BTree_Init(PBTNode *pt,char *s1,char *s2);
void PostOrder_Trav(PBTNode pt);
void Server(char *s1,char *s2,char *ls1,char *ls2,char *rs1,char *rs2);

int main()
{
	//FILE *fp;
	char s1[MAXSIZE];
	char s2[MAXSIZE];
	//fp = fopen("input.dat","r");
	//fscanf(fp,"%s",s1);
	//fscanf(fp,"%s",s2);
	gets(s1);
	gets(s2);
	PBTNode pt;
	BTree_Init(&pt,s1,s2);
	PostOrder_Trav(pt);
	//fclose(fp);
	//getchar();
	//getchar();
	return 0;
}

void Server(char *s1,char *s2,char *ls1,char *ls2,char *rs1,char *rs2)
{//ls1,ls2分配给左子树的串；rs1,rs2分配给右子树的串
	char flag=s2[0];//flag为先序列第一个字符
	int i;
	for(i=0;i<strlen(s1);i++){//得到根在串中的位置
		if(s1[i]==flag)break;
	}
	for(int j=0;j<i;j++)
		ls1[j] = s1[j];
	ls1[i] = '\0';

	int temp=0;
	for(int j=i+1;j<strlen(s1);j++)
		rs1[temp++] = s1[j];
	rs1[temp] = '\0';

	temp=0;
	for(i=1;i<strlen(ls1)+1;i++)
		ls2[temp++]=s2[i];
	ls2[temp]='\0';

	temp=0;
	for(i=strlen(ls1)+1;i<strlen(s2);i++){
		rs2[temp++]=s2[i];
	}
	rs2[temp]='\0';
}

void PostOrder_Trav(PBTNode pt)
{
	if(pt!=NULL){
		PostOrder_Trav(pt->lch);
		PostOrder_Trav(pt->rch);
		cout<<pt->elem<<endl;
	}
}

int BTree_Init(PBTNode *pt,char *s1,char *s2)
{//s1中序，s2前序
	if(s1[0]=='\0')*pt=NULL;
	else{
		char chnode=s2[0];
		*pt = (PBTNode)malloc(sizeof(BTNode));
		if(!(*pt))return 0;
		(*pt)->elem = chnode;
		char ls1[MAXSIZE],ls2[MAXSIZE],rs1[MAXSIZE],rs2[MAXSIZE];
		Server(s1,s2,ls1,ls2,rs1,rs2);
		BTree_Init(&((*pt)->lch),ls1,ls2);
		BTree_Init(&((*pt)->rch),rs1,rs2);
	}
}