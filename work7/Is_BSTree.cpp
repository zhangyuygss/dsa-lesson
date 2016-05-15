/*由先序表达式建立二叉树存储并按中序输出表达式
（先序递归建立二叉树并中序输出，并判断树是否是有序搜索树）*/
//提交时修改输入
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
FILE *fp;
int pre=-1,flag=1;//pre表示上一个输出的数，flag=1则输出是有序的
typedef struct BTNode{
	int elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

void BTree_Init(PBTNode *pt);
void InOrder_Trav(PBTNode pt);

int main()
{
	fp = fopen("input.dat","r");
	PBTNode pt;
	BTree_Init(&pt);
	InOrder_Trav(pt);
	//cout<<endl;
	if(flag)cout<<"It is an BinaryOrderTree!"<<endl;
	else cout<<"It is not an BinaryOrderTree!"<<endl;
	fclose(fp);
	getchar();
	getchar();
	return 0;
}

void InOrder_Trav(PBTNode pt)
{
	if(pt){
		InOrder_Trav(pt->lch);
		if(pre > pt->elem)flag = 0;
		cout<<pt->elem<<endl;
		pre = pt->elem;
		InOrder_Trav(pt->rch);
	}
}

void BTree_Init(PBTNode *pt)
{
	int val;
	fscanf(fp,"%d",&val);
	//cin>>val;
	if(val==0)*pt=NULL;
	else{
		*pt = (PBTNode)malloc(sizeof(BTNode));
		(*pt)->elem = val;
		BTree_Init(&((*pt)->lch));
		BTree_Init(&((*pt)->rch));
	}
}
