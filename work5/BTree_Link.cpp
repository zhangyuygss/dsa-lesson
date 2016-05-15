//filename:bitree.h

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define NIL '#'	//定义'#'为空节点

typedef struct queue_node qnode;
typedef struct bitree_node bitree;

struct bitree_node
{
	char elem;
	bitree *lchild;
	bitree *rchild;
};

/*队列节点*/
struct queue_node
{
	bitree *btn;
	qnode *next;
};

typedef struct link_queue
{
	qnode *head;
	qnode *tail;
}queue;


/*****队列的基本操作******/
int init_link_queue(queue *Q);
int is_queue_empty(queue Q);
int enqueue(queue *Q, bitree *btn);
int dequeue(queue *Q, char *elem);


/*****二叉树的操作*****/
bitree *create_bitree();
int is_bitree_empty(bitree *btn);
int get_bitree_depth(bitree *btn);
bitree *get_parent(bitree *btn, char elem);
int preorder_traverse(bitree *btn, int (*visit)(char));
int inorder_traverse(bitree *btn, int (*visit)(char));
int postorder_traverse(bitree *btn, int (*visit)(char));
int levelorder_traverse(bitree *btn, int (*visit)(char));
int destory_bitree(bitree *btn);
int print_elem(char elem);



//filename:queue.c

#include "bitree.h"

/* 
功能：链队列初始化 
*/
int init_link_queue(queue *Q)
{
	qnode *tmp_node = (qnode *)malloc(sizeof(qnode));
	if(!tmp_node)
	{
		return ERROR;
	}

	tmp_node->btn = NULL;
	tmp_node->next = NULL;
	Q->head = tmp_node;
	Q->tail = tmp_node;

	return OK;
}

/*
功能：队列是否为空 
返回：1 空；0 非空 
*/
int is_queue_empty(queue Q)
{
	return ((Q.head == Q.tail) ? TRUE : FALSE);
}

/* 
功能：元素num入队
*/
int enqueue(queue *Q, bitree *btn)
{
	qnode *tmp_node = (qnode *)malloc(sizeof(qnode));
	if(!tmp_node)
	{
		return ERROR;
	}

	tmp_node->next = NULL;
	tmp_node->btn = btn;
	Q->tail->next = tmp_node;
	Q->tail = tmp_node;

	return OK;
}


/* 
功能：出队，队头元素存入num
参数：	Q	队列； 
		btn_addr 存放出队节点内的bitree *地址
*/
int dequeue(queue *Q, int *btn_addr)
{
	qnode *tmp_node = NULL;
	if(is_queue_empty(*Q))
	{
		return ERROR;
	}

	tmp_node = Q->head->next;
	Q->head->next = tmp_node->next;
	*btn_addr = tmp_node->btn;

	if(Q->head->next == NULL)
	{
		Q->tail = Q->head;
	}

	free(tmp_node);

	return OK;
}


//filename:bitree.c

#include "bitree.h"

/*
功能：先序创建二叉树
返回：创建的节点地址
*/
bitree *create_bitree()
{
	char elem;
	bitree *btn = NULL;

	fflush(stdin);	//清空输入缓冲流
	scanf("%c", &elem);
	if(elem == NIL)
	{
		return btn;
	}
	else
	{
		btn = (bitree *)malloc(sizeof(bitree));
		btn->elem = elem;

		btn->lchild = create_bitree();
		btn->rchild = create_bitree();

		return btn;
	}
}

/*
功能：判断该二叉树是否为空
返回：1 空； 0 非空
*/
int is_bitree_empty(bitree *btn)
{
	if(!btn)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

/*
功能：求二叉树的深度
*/
int get_bitree_depth(bitree *btn)
{
	int i = 0;	//记录左子树深度
	int j = 0;	//记录右子树深度

	if(!btn)
	{
		return 0;
	}

	if(btn->lchild)
	{
		i = get_bitree_depth(btn->lchild);
	}
	else
	{
		i = 0;
	}

	if(btn->rchild)
	{
		j = get_bitree_depth(btn->rchild);
	}
	else
	{

		j = 0;
	}

	return (i > j) ? (i + 1) : (j + 1);
}

/*
功能：获取元素elem节点的父结点
返回：如果elem为根，返回NULL；
*/
bitree *get_parent(bitree *btn, char elem)
{
	int btn_addr = 0;
	bitree *father_node = NULL;
	queue Q;

	if(!btn)		//树为空
	{
		return NULL;
	}

	init_link_queue(&Q);	//初始化队列
	enqueue(&Q, btn);

	while(!is_queue_empty(Q))	//队列不为空
	{
		dequeue(&Q, &btn_addr);
		father_node = btn_addr;
		if((father_node->lchild && father_node->lchild->elem == elem) ||
			(father_node->rchild && father_node->rchild->elem == elem))
		{
			return father_node;
		}
		else
		{
			if(father_node->lchild)
			{
				enqueue(&Q, father_node->lchild);
			}
			if(father_node->rchild)
			{
				enqueue(&Q, father_node->rchild);
			}	
		}
	}

	return NULL;
}

/*
功能：先序遍历二叉树
*/
int preorder_traverse(bitree *btn, int (*visit)(char))
{
	if(!btn)
	{
		return OK;
	}

	visit(btn->elem);
	preorder_traverse(btn->lchild, visit);
	preorder_traverse(btn->rchild, visit);

	return OK;
}

/*
功能：中序遍历二叉树
*/
int inorder_traverse(bitree *btn, int (*visit)(char))
{
	if(!btn)
	{
		return OK;
	}

	inorder_traverse(btn->lchild, visit);
	visit(btn->elem);
	inorder_traverse(btn->rchild, visit);

	return OK;
}

/*
功能：后序遍历二叉树
*/
int postorder_traverse(bitree *btn, int (*visit)(char))
{
	if(!btn)
	{
		return OK;
	}

	postorder_traverse(btn->lchild, visit);
	postorder_traverse(btn->rchild, visit);
	visit(btn->elem);

	return OK;
}

/*
功能：按层序遍历二叉树，借助队列
*/
int levelorder_traverse(bitree *btn, int (*visit)(char))
{
	int btn_addr = 0;		//记录出队的队列节点的(bitree *)的地址
	bitree *bitree_node = NULL;
	queue Q;

	if(!btn)		//树为空
	{
		return NULL;
	}

	init_link_queue(&Q);	//初始化队列
	enqueue(&Q, btn);

	while(!is_queue_empty(Q))	//队列不为空
	{
		dequeue(&Q, &btn_addr);
		bitree_node = btn_addr;

		visit(bitree_node->elem);

		if(bitree_node->lchild)
		{
			enqueue(&Q, bitree_node->lchild);
		}
		if(bitree_node->rchild)
		{
			enqueue(&Q, bitree_node->rchild);
		}

	}

	return NULL;
}

/*
功能：	销毁二叉树
*/
int destory_bitree(bitree *btn)
{
	if(btn)
	{
		if(btn->lchild)
		{
			destory_bitree(btn->lchild);		
		}
		if(btn->rchild)
		{
			destory_bitree(btn->rchild);		
		}

		free(btn);
		btn = NULL;
	}

	return OK;
}

/*
功能：打印传入的参数值
*/
int print_elem(char elem)
{
	printf("%c ", elem);

	return OK;
}


//filename:test_bitree.c

#include "bitree.h"

/*
测试数据：	先序创建树：abd###c##;
先序遍历：	abdc
中序遍历：	dbac
后序遍历：	dbca
*/
int main(int argc, char *argv[])
{
	bitree *tmpnode = NULL;
	bitree *bitree = NULL;
	
	bitree = create_bitree();

	preorder_traverse(bitree, print_elem);
	printf("\n");
	inorder_traverse(bitree, print_elem);
	printf("\n");
	postorder_traverse(bitree, print_elem);
	printf("\n");
	levelorder_traverse(bitree, print_elem);
	printf("\n");

	printf("the depth of the bitree is %d.\n", get_bitree_depth(bitree));

	tmpnode = get_parent(bitree, 'd');
	printf("the 'd' father node is:%c\n", tmpnode->elem);

	destory_bitree(bitree);
	system("pause");

	return 0;
}
