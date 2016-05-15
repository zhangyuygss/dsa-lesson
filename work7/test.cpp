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
void Insert_BST(PBSTree pt,int key);
//nt DeleT_BST();
void Print_BST(PBSTree pt);

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
		Insert_BST(pt,elem);
	}
	Print_BST(pt);
	cout<<"-------------"<<endl;
	//fscanf(fp,"%d",&del);
	//DeleT_BST();
	//Print_BST();
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

void Insert_BST(PBSTree pt,int key)
{
	PBSTree pf;
	if(!Search_BST(&pf,NULL,pt,key)){
		PBSTree pnew;
		pnew = (PBSTree)malloc(sizeof(BSTree));
		pnew->elem = key;
		pnew->lch = pnew->rch = NULL;
		if(key < pf->elem)
			pf->lch = pnew;
		else
			pf->rch = pnew;
	}
}

//int DeleT_BST();
void Print_BST(PBSTree pt)
{
	if(pt){
		Print_BST(pt->lch);
		cout<<pt->elem<<endl;
		Print_BST(pt->rch);
	}
}
