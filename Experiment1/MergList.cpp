#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef struct Node{
	int dat;
	struct Node *next;
}Node,*PNode;

typedef struct Slink{
	PNode head;
	PNode tail;
}Slink,*PSlink;

PSlink Slink_Init(void);
int  Insert_Elem(int date,PNode pnode);
int Delet_Elem(PSlink pslink,int date);//删除数据为date的节点
int Input(PSlink pslink,int n);
int Output(PSlink pslink);
PNode Locate_Elem(PSlink pslink,int date);
int Inverse_Link(PSlink pslink);
int Merge_List(Slink slinkA,Slink slinkB,PSlink pslinkC);
void Delet_same(PSlink pslink,Slink slinkA,Slink slinkB);

int main()
{
	PSlink pslinklist=Slink_Init(),pslinklistA=Slink_Init(),
			pslinklistB=Slink_Init();
	int n1,n2,n3;
	cin>>n1>>n2>>n3;
	if(!Input(pslinklist,n1))return 1;
	if(!Input(pslinklistA,n2))return 2;
	if(!Input(pslinklistB,n3))return 3;
	Delet_same(pslinklist,*pslinklistA,*pslinklistB);
	if(!Output(pslinklist))return 5;
	return 0;
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
			pnodet->next=NULL;
		}
		else{
			cout<<"error_init"<<endl;
			pslink->head=NULL;
		}
	}
	else cout<<"error_init"<<endl;
	return pslink;
}


int Input(PSlink pslink,int n)
{
	PNode pnode,p;//p作为输入时的iterator
	p=pslink->head;
	for(;n>0;n--){
		pnode=(PNode)malloc(sizeof(Node));
		if(!pnode){
			cout<<"error_input "<<n<<endl;
			return 0;
		}
		int date;
		cin>>date;
		pnode->dat=date;
		p->next = pnode;
		p=pnode;
	}
	p->next=pslink->tail;
	return 1;
}

int Output(PSlink pslink)
{
	PNode p=pslink->head->next;
	while(p->next != NULL){
		cout<<p->dat<<endl;
		p=p->next;
	}
	return 1;
}

int  Insert_Elem(int date,PNode pnode)
{
	if(!pnode->next){
		cout<<"error_insert0"<<endl;
		return 0;
	}
	PNode p;
	p=(PNode)malloc(sizeof(Node));
	if(!p){
		cout<<"error_insert1"<<endl;
		return 0;
	}
	p->dat = date;
	p->next = pnode->next;
	pnode->next = p;
	return 1;
}

int Delet_Elem(PSlink pslink,int date)
{
	int flag=0;
	PNode p=pslink->head,ptemp;
	while(p->next != NULL){
		if(p->next->dat == date){
			ptemp=p->next;
			p->next = p->next->next;
			free(ptemp);
			p=p->next;
			flag++;
		}
		else p=p->next;
	}
	//if(!flag)cout<<"Not find"<<endl;
	return 1;
}

PNode Locate_Elem(PSlink pslink,int date)
{
	PNode p=pslink->head->next;
	while(p->next != NULL){
		if(p->dat == date)return p;
		p = p->next;
	}
	cout<<"Not find"<<endl;
	return pslink->head;//找不到元素时返回表头
}

int Inverse_Link(PSlink pslink)
{
	pslink->tail = pslink->head;
	PNode ppre=pslink->head,pcur=ppre->next,pnext;
	while(pcur->next != NULL){
		pnext=pcur->next;
		pcur->next = ppre;
		ppre=pcur;
		pcur=pnext;
	}
	pcur->next = ppre;
	pslink->head=pcur;
	pslink->tail->next = NULL;
	return 1;
}

int Merge_List(Slink slinkA,Slink slinkB,PSlink pslinkC)
{
	PNode	 pa, pb, pc; 
	pa = slinkA.head->next;	
	pb = slinkB.head->next; 
	pslinkC->head = pc = slinkA.head;	
	while (pa->next && pb->next) {
		if (pa->dat <= pb->dat) {
			    pc->next = pa; pc = pa; pa = pa->next;
		}
		else {
			    pc->next = pb; pc = pb; pb = pb->next;
		}
	}
	pc->next = pa->next ? pa : pb;
	return 1;
}

void Delet_same(PSlink pslink,Slink slinkA,Slink slinkB)
{
	PNode pa=slinkA.head->next,pb;
	while(pa->next){
		pb=slinkB.head->next;
		while(pb->next){
			if(pa->dat == pb->dat){
				Delet_Elem(pslink,pa->dat);
			}
			pb=pb->next;
		}
		pa=pa->next;
	}
}