/*递归建立括号构造的二叉树并层次输出*/
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#define MAXSIZE 110
using namespace std;

int cnt=0;

typedef struct BTNode{
	char elem;
	struct BTNode *lch,*rch;
}BTNode,*PBTNode;

/*队列节点*/
typedef struct Queue_Node
{
	PBTNode btn;
	struct Queue_Node *next;
}Qnode,*PQnode;

typedef struct Link_Queue
{
	Qnode *head;
	Qnode *tail;
}Queue,*PQueue;

/*****队列的基本操作******/
int Init_link_queue(Queue *Q);
int Is_queue_empty(Queue Q);
int Enqueue(Queue *Q, BTNode *btn);
int Dequeue(Queue *Q, PBTNode *btn_addr);

void BTree_Init(PBTNode *pt,char *s);
void SubString(char *sub1,char *sub2,char *s);
void Get_Leaf(PBTNode pt);
void Leval_Trav(PBTNode pt);

int main()
{
	//FILE *fp;
	//fp = fopen("input.dat","r");
	char s[MAXSIZE];
	//fscanf(fp,"%s",s);
	gets(s);
	PBTNode pt;
	BTree_Init(&pt,s);
	//Get_Leaf(pt);
	//cout<<cnt<<endl;
	Leval_Trav(pt);
	cout<<endl;
	//fclose(fp);
	return 0;
}

void Leval_Trav(PBTNode pt)
{
    Queue qu; PBTNode p;
    Init_link_queue(&qu);
    Enqueue (&qu, pt); 
    while ( !Is_queue_empty(qu) )  {
          Dequeue ( &qu, &p);
          cout<<p->elem;
          if ( p->lch != NULL )         		//Left child
               Enqueue ( &qu, p->lch );   	//EnQueue
          if ( p->rch != NULL )         		//Right child
               Enqueue ( &qu, p->rch );   	//EnQueue
     }
}

/* 
功能：链队列初始化 
*/
int Init_link_queue(Queue *Q)
{
	Qnode *tmp_node = (Qnode *)malloc(sizeof(Qnode));
	if(!tmp_node)return 0;
	tmp_node->btn = NULL;
	tmp_node->next = NULL;
	Q->head = tmp_node;
	Q->tail = tmp_node;
	return 1;
}

int Is_queue_empty(Queue Q)
{
	return ((Q.head == Q.tail));
}

/* 
功能：元素num入队
*/
int Enqueue(Queue *Q, BTNode *btn)
{
	Qnode *tmp_node = (Qnode *)malloc(sizeof(Qnode));
	if(!tmp_node)return 0;
	tmp_node->next = NULL;
	tmp_node->btn = btn;
	Q->tail->next = tmp_node;
	Q->tail = tmp_node;
	return 1;
}

/* 
功能：出队，队头元素存入num
参数：	Q	队列； 
		btn_addr 存放出队节点内的bitree *地址
*/
int Dequeue(Queue *Q, PBTNode *btn_addr)
{
	Qnode *tmp_node = NULL;
	if(Is_queue_empty(*Q))return 0;
	tmp_node = Q->head->next;
	Q->head->next = tmp_node->next;
	*btn_addr = tmp_node->btn;
	if(Q->head->next == NULL)
	{
		Q->tail = Q->head;
	}
	free(tmp_node);
	return 1;
}

void Get_Leaf(PBTNode pt)
{
	if(pt){
		if(pt->lch==NULL && pt->rch==NULL)cnt++;
		Get_Leaf(pt->lch);
		Get_Leaf(pt->rch);
	}
}

void BTree_Init(PBTNode *pt,char *s)
{
	if(strlen(s)==1){//叶子
		if(s[0]=='#')*pt=NULL;
		else {
			*pt = (PBTNode)malloc(sizeof(BTNode));
			(*pt)->elem = s[0];
			(*pt)->lch = NULL;
			(*pt)->rch = NULL;
		}
	}
	else{//子树
		*pt = (PBTNode)malloc(sizeof(BTNode));
		(*pt)->elem = s[0];
		char sub1[MAXSIZE]={0};
		char sub2[MAXSIZE]={0};
		SubString(sub1,sub2,s);
		BTree_Init(&((*pt)->lch),sub1);
		BTree_Init(&((*pt)->rch),sub2);
	}
}

void SubString(char *sub1,char *sub2,char *s)
{
	int j=0;
	for (int i = 2; i < strlen(s)-1; ++i)
		s[j++] = s[i];
	s[j]='\0';
	int bracnt=0;
	for(j=0; j<strlen(s); j++){
		if(s[j]=='(')bracnt++;
		else if(s[j]==')')bracnt--;
		if(s[j]==',' && bracnt==0)break;
	}
	for (int i = 0; i < j; ++i)
		sub1[i] = s[i];
	sub1[j]=='\0';
	int temp=0;
	for(int i=j+1; i<strlen(s); i++)
		sub2[temp++] = s[i];
	sub2[temp] = '\0';
}

