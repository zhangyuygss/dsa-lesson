#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

typedef struct CLNode
{
	int row, col, elem;
	struct CLNode *down, *right;
}CLNode, *PCLNode;

typedef struct CLink
{
	int rown, coln, elemn;
	PCLNode *rhead, *chead;
}CLink, *PCLink;

void CLink_Init(PCLink pcla, PCLink pclb);
void Add(PCLink, PCLink);
void Output(PCLink pcl);

int main()
{
	CLink  clb,*pclb=&clb, cla,*pcla = &cla;
	CLink_Init(pcla, pclb);
	Add(pcla,pclb);
	Output(pcla);
	cout << endl;
	getchar();
	getchar();
	return 0;
}

void Add(PCLink pcla, PCLink pclb)
{
	PCLNode pa,pb,pre=NULL,*rh,p;
	rh = (PCLNode*)malloc(sizeof(CLNode)*(pclb->coln));
	for (int i = 0; i < pcla->coln; ++i)
		rh[i] = pcla->chead[i];
	for (int i = 0; i < pcla->rown; ++i){
		pa = pcla->rhead[i];
		pb = pclb->rhead[i];
		pre=NULL;
		while(pb){
			if(pa==NULL || pa->col > pb->col){
				p=(PCLNode)malloc(sizeof(CLNode));
				p->row=pb->row;p->col=pb->col;p->elem=pb->elem;
				if(pre==NULL){
					pcla->rhead[i] = p;
				}
				else{
					pre->right = p;
				}
				p->right = pa;
				pre = p;
				//下面修改列
				if(pcla->chead[p->col] == NULL){
					pcla->chead[p->col] = p;
					p->down = NULL;
				}
				else{
					p->down = rh[p->col]->down;
					rh[p->col]->down = p;
				}
				rh[p->col] = p;
				pb = pb->right;
			}
			else if(pa->col < pb->col){
				pre = pa;
				pa = pa->right;
			}
			else if(pa->col == pb->col){
				int temp=pa->elem + pb->elem;
				if(!temp){
					if(!pre)pcla->rhead[i] = pa->right;
					else pre->right = pa->right;
					if(pcla->chead[pa->col] == pa)pcla->chead[pa->col] = rh[pa->col] = pa->down;
					else rh[pa->col]->down = pa->down;
					free(pa);
				}
				else pa->elem = pa->elem + pb->elem;
				pb = pb->right;
			}
			
		}
	}
}

void Output(PCLink pcl)
{
	for (int i = 0; i<pcl->rown; i++){
		PCLNode p = pcl->rhead[i];
		while (p){
			cout << p->row +1 << ' ' << p->col +1<< ' ' << p->elem << endl;
			p = p->right;
		}
	}
}

void CLink_Init(PCLink pcla, PCLink pclb)
{
	FILE *fp;
	fp = fopen("input.dat","r");
	int row, col, la, lb;
	//cin>>row>>col>>la>>lb;
	fscanf(fp,"%d%d%d%d",&row,&col,&la,&lb);
	pcla->rhead = (PCLNode*)malloc(sizeof(CLNode)*row);
	pcla->chead = (PCLNode*)malloc(sizeof(CLNode)*col);
	pclb->chead = (PCLNode*)malloc(sizeof(CLNode)*col);
	pclb->rhead = (PCLNode*)malloc(sizeof(CLNode)*row);
	pcla->rown = row;
	pclb->rown = row;
	pcla->coln = col;
	pclb->coln = col;
	pcla->elemn = la;
	pclb->elemn = lb;
	for (int i = 0; i<row; i++){//头节点初始化
		pcla->rhead[i] = NULL;
		pclb->rhead[i] = NULL;
	}
	for (int i = 0; i < col; ++i){
		pcla->chead[i] = NULL;
		pclb->chead[i] = NULL;
	}
	for (int i = 0; i<la; i++){
		int r, c, e;
		//cin>>r>>c>>e;
		fscanf(fp,"%d%d%d",&r,&c,&e);
		c-=1;r-=1;
		PCLNode p, q;
		p = (PCLNode)malloc(sizeof(CLNode));
		q = (PCLNode)malloc(sizeof(CLNode));
		p->row = r; p->col = c; p->elem = e;
		if (pcla->rhead[r] == NULL || pcla->rhead[r]->col > c){//插在行头
			p->right = pcla->rhead[r];
			pcla->rhead[r] = p;
		}
		else{
			for (q = pcla->rhead[r]; q->right && q->right->col < c ; q = q->right);//??
			p->right = q->right;
			q->right = p;
		}
		if (pcla->chead[c] == NULL || pcla->chead[c]->row > r){//插在列头
			p->down = pcla->chead[c];
			pcla->chead[c] = p;
		}
		else{
			for (q = pcla->chead[c]; q->down && q->down->row < r ; q = q->down);//??
			p->down = q->down;
			q->down = p;
		}
	}
	for (int i = 0; i<lb; i++){
		int r, c, e;
		//cin>>r>>c>>e;
		fscanf(fp,"%d%d%d",&r,&c,&e);
		c-=1;r-=1;
		PCLNode p, q;
		p = (PCLNode)malloc(sizeof(CLNode));
		q = (PCLNode)malloc(sizeof(CLNode));
		p->row = r; p->col = c; p->elem = e;
		if (pclb->rhead[r] == NULL || pclb->rhead[r]->col > c){//插在行头
			p->right = pclb->rhead[r];
			pclb->rhead[r] = p;
		}
		else{
			for (q = pclb->rhead[r]; q->right && q->right->col < c ; q = q->right);//??
			p->right = q->right;
			q->right = p;
		}
		if (pclb->chead[c] == NULL || pclb->chead[c]->row > r){//插在列头
			p->down = pclb->chead[c];
			pclb->chead[c] = p;
		}
		else{
			for (q = pclb->chead[c]; q->down && q->down->row < r ; q = q->down);//??
			p->down = q->down;
			q->down = p;
		}
	}
	fclose(fp);
}