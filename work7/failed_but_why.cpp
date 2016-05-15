#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int flag=0;//用于判断是否有区间里的数
FILE *fp;
typedef struct BinNode
{
	int key;
	struct BinNode *lnode,*rnode;
}BinNode,*PBinNode;

int SearchBST(PBinNode T,int key,PBinNode F,PBinNode *p);
int InsertBST(PBinNode *ppTree,int key);
void InOrder_Trav(PBinNode pt);
void InOrder_Trav_version2(PBinNode pt,int high,int low);//用于判断是否有区间里的数的变形遍历函数
void FindBetween(PBinNode pt);
void DeletBST(PBinNode *ppTree,int key);


int main()
{
	fp = fopen("input.dat","r");
	PBinNode t,*pT=&t;//这地方到底怎么搞
	*pT=NULL;
	int cnt;
	fscanf(fp,"%d",&cnt);
	//cin>>cnt;
	for(int i=0; i<cnt; i++){
		int key;
		fscanf(fp,"%d",&key);
		InsertBST(pT,key);
	}
	InOrder_Trav(*pT);
	cout<<endl;
	FindBetween(*pT);

	int keydelet;
	fscanf(fp,"%d",&keydelet);
	DeletBST(pT,keydelet);
	InOrder_Trav(*pT);
	getchar();
	getchar();
	return 0;
}

void DeletBST(PBinNode *ppTree,int key)
{
	PBinNode t,*p=&t,q,s;
	if(SearchBST(*ppTree,key,NULL,p)){
		if(!(*p)->rnode){//右空
			q = *p;
			*p = (*p)->lnode;
			free(q);
			cout<<1;
		}
		else if(!(*p)->lnode){
			q = *p;
			*p = (*p)->rnode;
			free(q);
		}
		else{
			q = *p;
			s = (*p)->lnode;
			while(s->rnode){
				q = s;
				s = s->rnode;
			}
			(*p)->key = s->key;
			if(q != *p)
				q->rnode = s->lnode;
			else q->lnode = s->lnode;
		}
	}
}


void FindBetween(PBinNode pt)
{
	int low,high;
	fscanf(fp,"%d%d",&low,&high);
	//cin>>low>>high;
	InOrder_Trav_version2(pt,high,low);
	if(!flag)cout<<"NOT FOUND"<<endl;
}

void InOrder_Trav_version2(PBinNode pt,int high,int low)
{
	if(pt){
		InOrder_Trav_version2(pt->lnode,high,low);
		if(pt->key < high  &&  pt->key > low){
			cout<<pt->key<<' ';
			flag = 1;
		}
		InOrder_Trav_version2(pt->rnode,high,low);
	}
}

void InOrder_Trav(PBinNode pt)
{
	if(pt){
		InOrder_Trav(pt->lnode);
		cout<<pt->key<<' ';
		InOrder_Trav(pt->rnode);
	}
}

int InsertBST(PBinNode *ppTree,int key)
{
	PBinNode t,*p=&t;
	if(!SearchBST(*ppTree,key,NULL,p)){
		PBinNode s;
		s=(PBinNode)malloc(sizeof(BinNode));
		s->key = key;
		s->lnode = s->rnode = NULL;
		if(*p==NULL)*ppTree=s;
		else if(key < (*p)->key)
			(*p)->lnode = s;
		else (*p)->rnode = s;
		return 1;
	}
	else return 0;
}

int SearchBST(PBinNode T,int key,PBinNode f,PBinNode *p)
{
	if(!T){
		*p = f;
		return 0;
	}
	else if(key == T->key){
		*p = T;
		return 1;
	}
	else if(key < T->key)
		return SearchBST(T->lnode,key,T,p);
	else
		return SearchBST(T->rnode,key,T,p);
}
