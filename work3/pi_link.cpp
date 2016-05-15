#include <cstdio>
#include <cstdlib>
#include <iostream>
#define maxlen 1100
#define maxcal 10000
using namespace std;

typedef struct Node{
	int dat;
	struct Node *pre;
	struct Node *next;
}Node,*PNode;

typedef struct Slink{
	PNode head;
	PNode tail;
}Slink,*PSlink;

PSlink Slink_Init(void);
int Output(PSlink pslink);
void Add(PSlink pres,PSlink pcur);
void Times(PSlink pcur,int num);
void Divide(PSlink pcur,int num);

int main()
{
	int dig;
	cin>>dig;
	PSlink res=Slink_Init(),cur=Slink_Init();//res为结果，cur为当前项
	int num1=1,num2=3;//num1分子，num2分母
	//计算pi
	res->head->next->next->dat = cur->head->next->next->dat = 2;
	for (int i = 0; i < maxcal; ++i)
	{
		Times(cur,num1);
		Divide(cur,num2);
		Add(res,cur);
		num1++;
		num2+=2;
	}
	cout<<"3.";
	PNode piter=res->head->next->next->next;
	for(int i=0;i<dig;i++){//display
		cout<<piter ->dat;
		piter =piter ->next;
	}
	cout<<endl;
	getchar();
	getchar();
	return 0;
}

void Add(PSlink pres,PSlink pcur)
{
	PNode p1=pres->tail->pre,p2=pcur->tail->pre;
	while(p1!=pres->head){
		int temp=0;
		temp=p1->dat + p2->dat;
		p1->dat = temp%10;
		p1->pre->dat += temp/10;
		p1 = p1->pre;
		p2 = p2->pre;
	}
}

void Times(PSlink pcur,int num)
{
	PNode p=pcur->tail->pre;
	int temp=0,buf=0;
	while(p->pre != pcur->tail){
		temp = (p->dat)*num+buf;
		p->dat = temp%10;
		buf = temp/10;//buf暂存进位
		p=p->pre;
	}
}

void Divide(PSlink pcur,int num)
{
	PNode p=pcur->head->next;
	int temp=0;//temp暂存被除数
	while(p->next != pcur->tail){
		p->dat = temp/num;
		temp = (temp%num)*10 + p->next->dat;
		p = p->next;
	}
}

PSlink Slink_Init(void)
{
	PSlink pslink;
	PNode pnodeh,pnodet;
	pslink=(PSlink)malloc(sizeof(Slink));
	if(pslink){
		pnodeh=(PNode)malloc(sizeof(Node));
		pnodet=(PNode)malloc(sizeof(Node));
		if(pnodeh&&pnodet){
			pslink->head = pnodeh;
			pslink->tail = pnodet;
			pnodeh->next=pnodet;
			pnodeh->pre=pnodet;
			pnodet->next=pnodeh;
			pnodet->pre=pnodeh;
		}
		else{
			cout<<"error_init"<<endl;
			pslink->head=NULL;
		}
	}
	else cout<<"error_init"<<endl;
	//1100位全部初始化为0
	for (int i = 0; i < maxlen; ++i)
	{
		PNode pnode,p=pslink->head;
		pnode=(PNode)malloc(sizeof(Node));
		pnode->dat=0;
		pnode->next = p->next;
		pnode->pre = p;
		p->next->pre = pnode;
		p->next = pnode;
	}
	return pslink;
}

int Output(PSlink pslink)
{
	PNode p=pslink->head->next;
	while(p->next != pslink->head){
		cout<<p->dat;
		p=p->next;
	}
	cout<<endl;
	return 1;
}

