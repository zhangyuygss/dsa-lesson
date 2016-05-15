//有头有尾的链表，头尾不存数据
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
FILE *fp;

typedef struct ListNode
{
	int elem;
	struct ListNode *nextnode;
}ListNode,*PListNode;

typedef struct List
{
	PListNode head;
	PListNode tail;
}List,*PList;

int List_Init(PList *plist,FILE *fp);
int Merg_List(PList *plistre,PList plist1,PList plist2);
void Print_List(List list);
void Rever_List(PList plist);

int main()
{
	fp = fopen("input.dat","r");
	PList plistre,plist1,plist2;
	if(!List_Init(&plist1,fp) || !List_Init(&plist2,fp))
		cout<<"Error In Init!"<<endl;
	if(!Merg_List(&plistre,plist1,plist2))
		cout<<"Error In Merge"<<endl;
	Print_List(*plistre);
	cout<<"----------"<<endl;
	Print_List(*plist2);
	cout<<"----------"<<endl;
	Rever_List(plist2);
	Print_List(*plist2);
	fclose(fp);
	return 0;
}

void Rever_List(PList plist)
{
	PListNode ptemp,ppre=plist->head,pcur=ppre->nextnode;
	ptemp = pcur->nextnode;
    //头变成新的尾
	ppre->nextnode = NULL;
	plist->tail = ppre;
	while(ptemp){
		pcur->nextnode = ppre;
		ppre = pcur;
		pcur = ptemp;
		ptemp = pcur->nextnode;
	}
	pcur->nextnode = ppre;//尾节点在循环中没有解决，此句解决

    plist->head = pcur;//头节点

}

int Merg_List(PList *plistre,PList plist1,PList plist2)
{
	PListNode p1=plist1->head->nextnode,p2=plist2->head->nextnode;
	*plistre = (PList)malloc(sizeof(List));
	PListNode p;
	p = (PListNode)malloc(sizeof(ListNode));//构造一个没有元素的头方便插入
	if(p){
		(*plistre)->head = p;
		(*plistre)->tail = p;
		while(p1->nextnode && p2->nextnode){
			int elem;
			if(p1->elem <= p2->elem){
				elem = p1->elem;
				p1 = p1->nextnode;
			}
			else {
				elem = p2->elem;
				p2 = p2->nextnode;
			}
			PListNode pnode;
			pnode =(PListNode)malloc(sizeof(ListNode));
			if(pnode){
				pnode->elem = elem;
				pnode->nextnode = NULL;
				(*plistre)->tail->nextnode = pnode;
				(*plistre)->tail = pnode;
			}
		}
		if(p1->nextnode){
			while(p1){
				PListNode pnode;
				pnode =(PListNode)malloc(sizeof(ListNode));
				if(pnode){
					pnode->elem = p1->elem;
					pnode->nextnode = NULL;
					(*plistre)->tail->nextnode = pnode;
					(*plistre)->tail = pnode;
				}
				p1 = p1->nextnode;
			}
		}
		else{
			while(p2){
				PListNode pnode;
				pnode =(PListNode)malloc(sizeof(ListNode));
				if(pnode){
					pnode->elem = p2->elem;
					pnode->nextnode = NULL;
					(*plistre)->tail->nextnode = pnode;
					(*plistre)->tail = pnode;
				}
				p2 = p2->nextnode;
			}
		}
	}
	return 1;
}

void Print_List(List list)
{
	PListNode p=list.head->nextnode;
	while(p->nextnode){
		cout<<p->elem<<endl;
		p = p->nextnode;
	}
}

int List_Init(PList *plist,FILE *fp)
{
	*plist = (PList)malloc(sizeof(List));
	PListNode p;
	p = (PListNode)malloc(sizeof(ListNode));//构造一个没有元素的头方便插入
	if(p){
		(*plist)->head = p;
		(*plist)->tail = p;
		int num;
		fscanf(fp,"%d",&num);
		for(int i=0; i<num; i++){
			int elem;
			fscanf(fp,"%d",&elem);
			PListNode pnode;
			pnode = (PListNode)malloc(sizeof(ListNode));
			if(pnode){
				pnode->elem = elem;
				pnode->nextnode = NULL;
				(*plist)->tail->nextnode = pnode;
				(*plist)->tail =pnode;
			}
		}
	}
	PListNode ptail;
	ptail = (PListNode)malloc(sizeof(ListNode));//构造一个没有元素的尾方便逆置
	if(ptail){
		(*plist)->tail->nextnode = ptail;
		ptail->nextnode = NULL;
	}
	return 1;
}
