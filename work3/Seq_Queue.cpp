#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXNUM 110
using namespace std;

typedef struct SeqQueue
{
	int q[MAXNUM];
	int rear,front;
}SeqQueue,*PseqQueue;

PseqQueue Init_SeqQueue(int m);
int Delet_Elem(PseqQueue,int);
int Insert_Elem(PseqQueue,int,int);


int main()
{
	int n,m;//n 为输入元素个数，m 为数组大小
	cin>>n>>m;
	m++;
	SeqQueue *psq=Init_SeqQueue(m);
	for (int i = 0; i < n; ++i)
	{
		int temp;
		cin>>temp;
		if(!temp){
			cout<<Delet_Elem(psq,m)<<endl;
		}
		else Insert_Elem(psq,temp,m);
	}
	return 0;
}

PseqQueue Init_SeqQueue(int m)
{
	SeqQueue seq,*pseq;
	pseq=(PseqQueue)malloc(sizeof(SeqQueue));
	if(pseq){
		pseq->rear = pseq->front = 0;
		return pseq;
	}
	else {
		cout<<"No Space for Init!"<<endl;
		exit(1);
	}
}

int Insert_Elem(PseqQueue pseq,int date,int m)  
{
	if((pseq->rear + 1)%m == pseq->front){
		cout<<"No"<<endl;
	}
	else{
		pseq->q[pseq->rear] = date;
		pseq->rear = (pseq->rear + 1)%m;
	}
	return 1;
}

int Delet_Elem(PseqQueue pseq,int m)
{
	if(pseq->rear == pseq->front){
		cout<<"Already Empty!"<<endl;
	}
	else{
		int k=pseq->q[pseq->front];
		pseq->front = (pseq->front + 1)%m;
		return k;
	}
}