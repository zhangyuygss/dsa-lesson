//斐波那契，循环队列
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXNUM 110
using namespace std;

typedef struct SeqQueue
{
	int data[MAXNUM];
	int rear,front;
	int maxlength;
}SeqQueue,*PseqQueue;

void SQ_Init(PseqQueue *ppsq);
int SQ_Dequeue(PseqQueue psq);
int SQ_Inqueue(PseqQueue psq,int elem);

int Fibonaci(void);

int main()
{
	cout<<Fibonaci()<<endl;
	getchar();
	getchar();
	return 0;
}

void SQ_Init(PseqQueue *ppsq)
{
	(*ppsq) = (PseqQueue)malloc(sizeof(SeqQueue));
	if(*ppsq){
		int len;
		cin>>len;
		(*ppsq)->maxlength = len;
		(*ppsq)->front = (*ppsq)->rear = 0;
	}
}

int SQ_Dequeue(PseqQueue psq)
{
	if(psq->front == psq->rear){
		cout<<"Empty Queue!"<<endl;
	}
	else{
		int temp=psq->data[psq->front];
		psq->front = (psq->front+1)%psq->maxlength;
		return temp;
	}
	return 0;
}

int  SQ_Inqueue(PseqQueue psq,int elem)
{
	if((psq->rear + 1)%psq->maxlength == psq->front){
		cout<<"No Space!"<<endl;
		return 0;
	}
	else{
		psq->data[psq->rear] = elem;
		psq->rear = (psq->rear+1)%psq->maxlength;
		return 1;
	}
}

int Fibonaci(void)
{
	PseqQueue psq;
	SQ_Init(&psq);
	int target;
	cin>>target;
	SQ_Inqueue(psq,1);
	SQ_Inqueue(psq,1);
	int cnt=1,pre;//cnt表示到数列第cnt项
	while(psq->data[(psq->rear + psq->maxlength -1)%psq->maxlength] < target){
        cout<<"rear:"<<psq->rear<<"front:"<<psq->front<<endl;
		SQ_Inqueue(psq,psq->data[(psq->rear + psq->maxlength -1)%psq->maxlength] +
			psq->data[(psq->rear + psq->maxlength -2)%psq->maxlength]);
		SQ_Dequeue(psq);
		cnt++;
        pre = psq->data[(psq->rear + psq->maxlength -2)%psq->maxlength];
	}
	return pre;//pre表示前一项数值

}
