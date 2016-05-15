#include <cstdio>
#include <cstdlib>
#include <iostream>
#define maxsize 2000
using namespace std;

typedef struct
{
	int row,col;
	int elem;
}Triple;

typedef struct
{
	Triple data[maxsize];
	int rown,coln,datan;
}Matrix,*PMatrix;

void Input(PMatrix pma, PMatrix pmb);
void Add(PMatrix pma,PMatrix pmb,PMatrix pmc);
void Output(PMatrix pm);

int main()
{
	Matrix *pmatrixA,*pmatrixB,*pmatrixC;
	pmatrixA=(PMatrix)malloc(sizeof(Matrix));
	pmatrixB=(PMatrix)malloc(sizeof(Matrix));
	pmatrixC=(PMatrix)malloc(sizeof(Matrix));
	Input(pmatrixA,pmatrixB);
	Add(pmatrixA,pmatrixB,pmatrixC);
	Output(pmatrixC);
	//getchar();
	//getchar();
	return 0;
}

void Output(PMatrix pm)
{
	for (int i = 0; i < pm->datan; ++i)
	{
		cout<<pm->data[i].row +1<<' '<<pm->data[i].col+1<<' '<<pm->data[i].elem<<endl;
	}
}

void Add(PMatrix pma,PMatrix pmb,PMatrix pmc)
{
	int cnta=0,cntb=0,cntc=0;
	while(cnta<pma->datan && cntb<pmb->datan){
		int ra=pma->data[cnta].row, ca=pma->data[cnta].col, 
			rb=pmb->data[cntb].row, cb=pmb->data[cntb].col;
		if(ra<rb){
			pmc->data[cntc].row = ra;
			pmc->data[cntc].col = ca;
			pmc->data[cntc++].elem = pma->data[cnta++].elem;//a表后移，c表后移
		}
		else if(ra>rb){
			pmc->data[cntc].row = rb;
			pmc->data[cntc].col = cb;
			pmc->data[cntc++].elem = pmb->data[cntb++].elem;//b表后移，c表后移
		}
		else if(ra==rb){
			if(ca<cb){
			pmc->data[cntc].row = ra;
			pmc->data[cntc].col = ca;
			pmc->data[cntc++].elem = pma->data[cnta++].elem;//a表后移，c表后移
			}
			if(ca>cb){
				pmc->data[cntc].row = rb;
				pmc->data[cntc].col = cb;
				pmc->data[cntc++].elem = pmb->data[cntb++].elem;//b表后移，c表后移
			}
			else if(ca==cb){
				if(pma->data[cnta].elem + pmb->data[cntb].elem == 0){
					cntb++;cnta++;
				}
				else{
					pmc->data[cntc].row = ra;
					pmc->data[cntc].col = ca;
					pmc->data[cntc++].elem = pma->data[cnta++].elem + pmb->data[cntb++].elem;//abc同时后移
				}
			}
		}
	}
	pmc->datan = cntc;
	pmc->rown = pma->rown;
	pmc->coln = pma->coln;
}

void Input(PMatrix pma, PMatrix pmb)
{//输入两个矩阵
	int row,col,la,lb;
	cin>>row>>col>>la>>lb;
	pma->rown = pmb->rown = row;
	pma->coln = pmb->coln = col;
	pma->datan = la;
	pmb->datan = lb;
	for (int i = 0; i < la; ++i)
	{
		int r,c,data;
		cin>>r>>c>>data;
		pma->data[i].row = r-1;
		pma->data[i].col = c-1;
		pma->data[i].elem = data;
	}
	for (int i = 0; i < lb; ++i)
	{
		int r,c,data;
		cin>>r>>c>>data;
		pmb->data[i].row = r-1;
		pmb->data[i].col = c-1;
		pmb->data[i].elem = data;
	}
}
