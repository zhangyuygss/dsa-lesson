/*先序递归建立二叉树并求叶子数*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int cnt=0;

typedef struct BTNode{
	char elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

void BTree_Init(PBTNode *pt);
void Get_Leaf(PBTNode pt);

int main()
{
	//FILE *fp;
	//fp = fopen("input.dat","r");
	PBTNode pt;
	BTree_Init(&pt);
	Get_Leaf(pt);
	cout<<cnt<<endl;
	//fclose(fp);
	return 0;
}

void Get_Leaf(PBTNode pt)
{
	if(pt){
		if(pt->lch==NULL && pt->rch==NULL)cnt++;
		Get_Leaf(pt->lch);
		Get_Leaf(pt->rch);
	}
}

void BTree_Init(PBTNode *pt)
{
	char ch;
	//fscanf(fp,"%c",&ch);
	cin>>ch;
	if(ch=='#')*pt=NULL;
	else{
		*pt = (PBTNode)malloc(sizeof(BTNode));
		(*pt)->elem = ch;
		ch = 'f';
		BTree_Init(&((*pt)->lch));
		BTree_Init(&((*pt)->rch));
	}
}