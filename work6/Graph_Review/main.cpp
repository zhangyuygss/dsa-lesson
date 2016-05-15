#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAXSIZE 100
using namespace std;
FILE *fp;
typedef struct Arc
{
	int endvex;
	struct Arc *nextarc;
}Arc,*PArc;

typedef struct Vex
{
	int elem;
	PArc arclist;
}Vex,*PVex;

typedef struct Graph
{
	Vex gvex[MAXSIZE];
	int arcnum,vexnum;
}Graph,*PGraph;

int Init_Graph(PGraph pg,FILE  *fp);
void DFSList(Graph g,int start,int *visited);
int DFS(PGraph pg);

int main()
{
	fp = fopen("input.dat","r");
	Graph g;
	Init_Graph(&g,fp);
	DFS(&g);
	getchar();
	getchar();
	fclose(fp);
	return 0;
}

int Init_Graph(PGraph pg,FILE *fp)
{
	int arcnum;
	fscanf(fp,"%d",&arcnum);
	pg->arcnum = arcnum;
	for(int i=0; i<MAXSIZE; i++){
		pg->gvex[i].elem = -1;//-1表示不存在节点
		pg->gvex[i].arclist = NULL;
	}
	for(int i=0; i<arcnum; i++){
		int start,end;
		fscanf(fp,"%d%d",&start,&end);
		PArc pa;
		pa = (PArc)malloc(sizeof(Arc));
		pa->endvex = end;
		pa->nextarc = pg->gvex[start].arclist;
		pg->gvex[start].arclist = pa;
		pg->gvex[start].elem = start;
	}
	return 1;
}

void DFSList(Graph g,int start,int *visited)
{
	visited[start]=1;
	cout<<g.gvex[start].elem<<endl;;
	PArc parc=g.gvex[start].arclist;
	while(parc){
		DFSList(g,parc->endvex,visited);
		parc = parc->nextarc;
	}
}

int DFS(PGraph pg)
{
	int visited[MAXSIZE]={0};
	for(int i=0; i<MAXSIZE; i++){
		if(!visited[i] && pg->gvex[i].elem!= -1){
			DFSList(*pg,i,visited);
		}
	}
}
