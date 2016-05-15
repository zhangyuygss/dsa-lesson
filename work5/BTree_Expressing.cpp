/*由先序表达式建立二叉树存储并按中序输出表达式
（先序递归建立二叉树并中序输出）*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
//FILE *fp;
typedef struct BTNode{
	char elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

void BTree_Init(PBTNode *pt);
void InOrder_Trav(PBTNode pt);

int main()
{
	//fp = fopen("input.dat","r");
	PBTNode pt;
	BTree_Init(&pt);
	//Get_Leaf(pt);
	//cout<<cnt<<endl;
	InOrder_Trav(pt);
	cout<<endl;
	//fclose(fp);
	//getchar();
	//getchar();
	return 0;
}

void InOrder_Trav(PBTNode pt)
{
	if(pt){
		InOrder_Trav(pt->lch);
		cout<<pt->elem;
		InOrder_Trav(pt->rch);
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
		BTree_Init(&((*pt)->lch));
		BTree_Init(&((*pt)->rch));
	}
}