/*由先序表达式建立二叉树存储并按中序输出表达式
（先序递归建立二叉树并中序输出，并判断树是否是有序搜索树）*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
FILE *fp;
typedef struct BTNode{
	int elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

void BTree_Init(PBTNode *pt);
void InOrder_Trav(PBTNode pt);
int SearchBST(PBTNode T,int elem,PBTNode F,PBTNode *p);
int InsertBST(PBTNode *ppTree,int elem);
void MergBST(PBTNode *pt,PBTNode pt2);

int main()
{
	fp = fopen("input.dat","r");
	PBTNode pt1,pt2;
	BTree_Init(&pt1);
	BTree_Init(&pt2);
	MergBST(&pt1,pt2);
	InOrder_Trav(pt1);
	//cout<<endl;
	fclose(fp);
	getchar();
	getchar();
	return 0;
}

void MergBST(PBTNode *pt,PBTNode pt2)
{
	if(pt2){
		MergBST(pt,pt2->lch);
		InsertBST(pt,pt2->elem);

		MergBST(pt,pt2->rch);
	}
}

int InsertBST(PBTNode *ppTree,int elem)
{
	PBTNode t,*p=&t;
	if(!SearchBST(*ppTree,elem,NULL,p)){
		PBTNode s;
		s=(PBTNode)malloc(sizeof(BTNode));
		s->elem = elem;
		s->lch = s->rch = NULL;
		if(*p==NULL)*ppTree=s;
		else if(elem < (*p)->elem)
			(*p)->lch = s;
		else (*p)->rch = s;
		return 1;
	}
	else return 0;
}

int SearchBST(PBTNode T,int elem,PBTNode f,PBTNode *p)
{
	if(!T){
		*p = f;
		return 0;
	}
	else if(elem == T->elem){
		*p = T;
		return 1;
	}
	else if(elem < T->elem)
		return SearchBST(T->lch,elem,T,p);
	else
		return SearchBST(T->rch,elem,T,p);
}

void InOrder_Trav(PBTNode pt)
{
	if(pt){
		InOrder_Trav(pt->lch);
		cout<<pt->elem<<endl;
		InOrder_Trav(pt->rch);
	}
}

void BTree_Init(PBTNode *pt)
{
	int val;
	fscanf(fp,"%d",&val);
	//cin>>val;
	if(val==-1)*pt=NULL;
	else{
		*pt = (PBTNode)malloc(sizeof(BTNode));
		(*pt)->elem = val;
		BTree_Init(&((*pt)->lch));
		BTree_Init(&((*pt)->rch));
	}
}

//注释部分可直接提交
/*
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int tag=0;
//FILE *fp;
typedef struct BTNode{
	int elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

void BTree_Init(PBTNode *pt);
void InOrder_Trav(PBTNode pt);
int SearchBST(PBTNode T,int elem,PBTNode F,PBTNode *p);
int InsertBST(PBTNode *ppTree,int elem);
void MergBST(PBTNode *pt,PBTNode pt2);

int main()
{
	//fp = fopen("input.dat","r");
	PBTNode pt1,pt2;
	BTree_Init(&pt1);
	BTree_Init(&pt2);
	MergBST(&pt1,pt2);
	InOrder_Trav(pt1);
	tag=0;
	cout<<endl;
	//fclose(fp);
	//getchar();
	//getchar();
	return 0;
}

void MergBST(PBTNode *pt,PBTNode pt2)
{
	if(pt2){
		MergBST(pt,pt2->lch);
		InsertBST(pt,pt2->elem);

		MergBST(pt,pt2->rch);
	}
}

int InsertBST(PBTNode *ppTree,int elem)
{
	PBTNode t,*p=&t;
	if(!SearchBST(*ppTree,elem,NULL,p)){
		PBTNode s;
		s=(PBTNode)malloc(sizeof(BTNode));
		s->elem = elem;
		s->lch = s->rch = NULL;
		if(*p==NULL)*ppTree=s;
		else if(elem < (*p)->elem)
			(*p)->lch = s;
		else (*p)->rch = s;
		return 1;
	}
	else return 0;
}

int SearchBST(PBTNode T,int elem,PBTNode f,PBTNode *p)
{
	if(!T){
		*p = f;
		return 0;
	}
	else if(elem == T->elem){
		*p = T;
		return 1;
	}
	else if(elem < T->elem)
		return SearchBST(T->lch,elem,T,p);
	else
		return SearchBST(T->rch,elem,T,p);
}

void InOrder_Trav(PBTNode pt)
{
	if(pt){
		InOrder_Trav(pt->lch);
		if(tag){
			cout<<' '<<pt->elem;
		}
		else {
			cout<<pt->elem;
			tag++;
		}
		InOrder_Trav(pt->rch);
	}
}

void BTree_Init(PBTNode *pt)
{
	int val;
	//fscanf(fp,"%d",&val);
	cin>>val;
	if(val==-1)*pt=NULL;
	else{
		*pt = (PBTNode)malloc(sizeof(BTNode));
		(*pt)->elem = val;
		BTree_Init(&((*pt)->lch));
		BTree_Init(&((*pt)->rch));
	}
}

*/