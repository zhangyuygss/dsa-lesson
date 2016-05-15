#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct BSTree
{
	int elem;
	struct BSTree *lch,*rch;
}BSTree,*PBSTree;

int Search_BST(PBSTree *ppresult,PBSTree father,PBSTree pt,int key);
void Insert_BST(PBSTree *ppt,int key);
void Print_BST(PBSTree pt);
void Delete(PBSTree *ppt);
int DeleteBST (PBSTree *T, int key);


int main()
{
	PBSTree pt = NULL;
	int cnt,del;
	FILE *fp;
	fp = fopen("input.dat","r");
	fscanf(fp,"%d",&cnt);
	for(int i=0; i<cnt; i++){
		int elem;
		fscanf(fp,"%d",&elem);
		Insert_BST(&pt,elem);
	}
	Print_BST(pt);
	cout<<"-------------"<<endl;
	fscanf(fp,"%d",&del);
	DeleteBST(&pt,del);
	Print_BST(pt);
	getchar();
	getchar();
	return 0;
}


int Search_BST(PBSTree *ppresult,PBSTree father,PBSTree pt,int key)
{
	if(!pt){
		(*ppresult) = father;
		return 0;
	}
	else if(pt->elem < key)
		Search_BST(ppresult,pt,pt->rch,key);
	else if(pt->elem >key)
		Search_BST(ppresult,pt,pt->lch,key);
	else{
		(*ppresult) = pt;
		return 1;
	}
}

void Insert_BST(PBSTree *ppt,int key)
{
	PBSTree pf;
	if(!Search_BST(&pf,NULL,*ppt,key)){
		PBSTree pnew;
		pnew = (PBSTree)malloc(sizeof(BSTree));
		pnew->elem = key;
		pnew->lch = pnew->rch = NULL;
		if(!(*ppt))(*ppt) =pnew;
		else{
			if(key < pf->elem)
				pf->lch = pnew;
			else
				pf->rch = pnew;
		}
	}
}
int DeleteBST (PBSTree *T, int key)
{
	/* 若二叉树中存在关键字等于key的元素时，则删除该元素 */
	if (!(*T))
		return 0;
	else
	{
		if (key == (*T)->elem)	
			Delete (T);
		else if (key < (*T)->elem)
			DeleteBST (&(*T)->lch, key);
		else
			DeleteBST (&(*T)->rch, key);
	}
}

void Delete(PBSTree *ppt)
{
	if(!(*ppt)->lch){
		PBSTree ptemp = *ppt;
		(*ppt) = (*ppt)->rch;
		free(ptemp);
	}
	else if(!(*ppt)->rch){
		PBSTree ptemp = *ppt;
		(*ppt) = (*ppt)->lch;
		free(ptemp);	
	}
	else{
		PBSTree q=*ppt,s=(*ppt)->lch;
		while(s->rch){
			q = s; s = s->rch;
		}
		(*ppt)->elem = s->elem;
		if(q!=*ppt)
			q->rch  = s->lch;
		else q->lch = s->lch;
	}
}

void Print_BST(PBSTree pt)
{
	if(pt){
		Print_BST(pt->lch);
		cout<<pt->elem<<endl;
		Print_BST(pt->rch);
	}
}
