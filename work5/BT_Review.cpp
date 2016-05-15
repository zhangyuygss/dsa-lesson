#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#define MAXSIZE 110
using namespace std;
FILE *fp;
typedef struct BTree
{
	char elem;
	struct BTree *lchild,*rchild;
}BTree,*PBTree;

void BTree_PreOrder_Init(PBTree *ppbt,FILE *fp);
void BTree_InOrder_Traver(PBTree pbt);

int main()
{
	fp = fopen("input.dat","r");
	PBTree pbt;
	BTree_PreOrder_Init(&pbt,fp);
	BTree_InOrder_Traver(pbt);
	cout<<endl;
	fclose(fp);
	getchar();
	getchar();
	return 0;
}


void BTree_PreOrder_Init(PBTree *ppbt,FILE *fp)
{
	char ch;
	fscanf(fp,"%c",&ch);
	if(ch == '#')
		(*ppbt)=NULL;
	else{
		(*ppbt) = (PBTree)malloc(sizeof(BTree));
		if(*ppbt){
			(*ppbt)->elem = ch;
			BTree_PreOrder_Init(&((*ppbt)->lchild),fp);
			BTree_PreOrder_Init(&((*ppbt)->rchild),fp);
		}
	}
	
}

void BTree_InOrder_Traver(PBTree pbt)
{
	if(pbt){
		BTree_InOrder_Traver(pbt->lchild);
		cout<<pbt->elem;
		BTree_InOrder_Traver(pbt->rchild);
	}
}