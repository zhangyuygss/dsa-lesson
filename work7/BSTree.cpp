//完成二叉搜索树的建立于删除
//输出会格式错误，后面注释代码规范了输出
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int flag=0;//用于判断是否有区间里的数
//FILE *fp;
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
int DeleteBST (PBinNode *T, int key);
void Delete (PBinNode *p);

int main()
{
	//fp = fopen("input.dat","r");
	PBinNode t,*pT=&t;//这地方到底怎么搞
	*pT=NULL;
	int cnt;
	//fscanf(fp,"%d",&cnt);
	cin>>cnt;
	for(int i=0; i<cnt; i++){
		int key;
		//fscanf(fp,"%d",&key);
		cin>>key;
		InsertBST(pT,key);
	}
	InOrder_Trav(*pT);
	cout<<endl;
	FindBetween(*pT);
	cout<<endl;

	int keydelet;
	//fscanf(fp,"%d",&keydelet);
	cin>>keydelet;
	DeleteBST(pT,keydelet);
	InOrder_Trav(*pT);
	cout<<endl;

	int keyinsert;
	//fscanf(fp,"%d",&keyinsert);
	cin>>keyinsert;
	InsertBST(pT,keyinsert);
	InOrder_Trav(*pT);
	cout<<endl;

	//getchar();
	//getchar();
	return 0;
}

int DeleteBST (PBinNode *T, int key)
{
	/* 若二叉树中存在关键字等于key的元素时，则删除该元素 */
	if (!(*T))
		return 0;
	else
	{
		if (key == (*T)->key)	
			Delete (T);
		else if (key < (*T)->key)
			DeleteBST (&(*T)->lnode, key);
		else
			DeleteBST (&(*T)->rnode, key);
	}
}


void Delete (PBinNode *p) {
/* 删除*p所指向的结点，并重接它的左右子树 */
	PBinNode  q, s;
	if (!(*p)->rnode) {	/* 右子树空，重接左子树 */
		q = *p;	*p = (*p)->lnode;  free(q);
	}
	else if (!(*p)->lnode) {	/* 左子树空，重接右子树 */
		q = *p;  *p = (*p)->rnode;  free(q);
	}
	else{				/* 左右子树均不空 */
		q = *p;  s = (*p)->lnode;
		while (s->rnode) {	/* 向右走到尽头 */
			q = s;  s = s->rnode;
		}
		(*p)->key = s->key;	/* 用s替换p */
		if (q != *p)	q->rnode = s->lnode;
		else		q->lnode = s->lnode;
		free(s);
	}
}



void FindBetween(PBinNode pt)
{
	int low,high;
	//fscanf(fp,"%d%d",&low,&high);
	cin>>low>>high;
	InOrder_Trav_version2(pt,high,low);
	if(!flag)cout<<"NOT FOUND";
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


/*
//注释内容可提交
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
int flag=0;//用于判断是否有区间里的数
//FILE *fp;
int tag=0;//用于规范输出的小技俩
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
int DeleteBST (PBinNode *T, int key);
void Delete (PBinNode *p);

int main()
{
	//fp = fopen("input.dat","r");
	PBinNode t,*pT=&t;//这地方到底怎么搞
	*pT=NULL;
	int cnt;
	//fscanf(fp,"%d",&cnt);
	cin>>cnt;
	for(int i=0; i<cnt; i++){
		int key;
		//fscanf(fp,"%d",&key);
		cin>>key;
		InsertBST(pT,key);
	}
	InOrder_Trav(*pT);
	tag=0;
	cout<<endl;
	FindBetween(*pT);
	cout<<endl;

	int keydelet;
	//fscanf(fp,"%d",&keydelet);
	cin>>keydelet;
	DeleteBST(pT,keydelet);
	InOrder_Trav(*pT);
	tag=0;

	cout<<endl;

	int keyinsert;
	//fscanf(fp,"%d",&keyinsert);
	cin>>keyinsert;
	InsertBST(pT,keyinsert);
	InOrder_Trav(*pT);
	tag=0;

	cout<<endl;

	//getchar();
	//getchar();
	return 0;
}

int DeleteBST (PBinNode *T, int key)
{
	//若二叉树中存在关键字等于key的元素时，则删除该元素 
	if (!(*T))
		return 0;
	else
	{
		if (key == (*T)->key)	
			Delete (T);
		else if (key < (*T)->key)
			DeleteBST (&(*T)->lnode, key);
		else
			DeleteBST (&(*T)->rnode, key);
	}
}


void Delete (PBinNode *p) {
// 删除*p所指向的结点，并重接它的左右子树 
	PBinNode  q, s;
	if (!(*p)->rnode) {	
		q = *p;	*p = (*p)->lnode;  free(q);
	}
	else if (!(*p)->lnode) {	
		q = *p;  *p = (*p)->rnode;  free(q);
	}
	else{				
		q = *p;  s = (*p)->lnode;
		while (s->rnode) {	
			q = s;  s = s->rnode;
		}
		(*p)->key = s->key;	
		if (q != *p)	q->rnode = s->lnode;
		else		q->lnode = s->lnode;
		free(s);
	}
}



void FindBetween(PBinNode pt)
{
	int low,high;
	//fscanf(fp,"%d%d",&low,&high);
	cin>>low>>high;
	InOrder_Trav_version2(pt,high,low);
	tag=0;
	
	if(!flag)cout<<"NOT FOUND";
}

void InOrder_Trav_version2(PBinNode pt,int high,int low)
{
	if(pt){
		InOrder_Trav_version2(pt->lnode,high,low);
		if(pt->key < high  &&  pt->key > low){
			if(tag){
				cout<<' '<<pt->key;
			}
			else{
				cout<<pt->key;
				tag=1;
			}
			flag = 1;
		}
		InOrder_Trav_version2(pt->rnode,high,low);
	}
}

void InOrder_Trav(PBinNode pt)
{
	if(pt){
		InOrder_Trav(pt->lnode);
		if(tag){
				cout<<' '<<pt->key;
			}
		else{
			cout<<pt->key;
			tag=1;
		}
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

*/
