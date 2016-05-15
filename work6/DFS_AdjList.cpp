#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXVEX 101
#define VISITED 1
#define UNVISITED 0
using namespace std;
int flag = 0;
FILE *fp;
typedef struct EdgeNode
{
	int endvex;
	int weight;
	struct EdgeNode *nextedge;
}EdgeNode,*PEdgenode;

typedef struct 
{
	int vertex;
	PEdgenode edgelist;
}VexNode;

typedef struct 
{
	VexNode vexs[MAXVEX];
	int vexnum,edgenum;
}GraphList;


void CreatGraph(GraphList *g,int targtnum,FILE *fp)
{
	g->vexnum = 100;
	g->edgenum = targtnum;
	for(int i=0; i<MAXVEX; i++){
		g->vexs[i].vertex = i;//0~maxvex-1个节点，分别用0~maxvex-1表示
		g->vexs[i].edgelist = NULL;
	}
	for(int i=0; i<targtnum; i++){
		int vex1,vex2;
		PEdgenode p;
		fscanf(fp,"%d%d",&vex1,&vex2);
		//cin>>vex1>>vex2;
		p = (PEdgenode)malloc(sizeof(EdgeNode));
		p->endvex = vex2;
		//p->weight = 0;
		p->nextedge = g->vexs[vex1].edgelist;
		g->vexs[vex1].edgelist = p;
	} 
}

void DFSInList(GraphList *pg,int visited[],int start,int end)
{
	if(start==end)flag=1;
	visited[start] = VISITED;
	PEdgenode p=pg->vexs[start].edgelist;
	while(p!=NULL){
		if(!visited[p->endvex])
			DFSInList(pg,visited,p->endvex,end);
		p = p->nextedge;
	}
}

void DFS_Trav(GraphList *pg,FILE *fp)
{
	int start,end;
	int visited[MAXVEX];
	fscanf(fp,"%d%d",&start,&end);
	//cin>>start>>end;
	for(int i=0; i<MAXVEX; i++)visited[i]=UNVISITED;
	DFSInList(pg,visited,start,end);
	if(flag)cout<<"Y"<<endl;
	else cout<<"N"<<endl;
}

int main()
{
	fp = fopen("input.dat","r");
	int egnum,targtnum;
	fscanf(fp,"%d%d",&egnum,&targtnum);
	//cin>>egnum>>targtnum;
	GraphList Graph,*PGraph=&Graph;
	CreatGraph(PGraph,egnum,fp);
	for(int i=0; i<targtnum; i++){
		flag = 0;
		DFS_Trav(PGraph,fp);
	}
	fclose(fp);
	getchar();
	getchar();
	return 0;
}