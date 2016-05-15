#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXSIZE 50
#define INF 10000
using namespace std;
FILE *fp;

typedef struct MGraph
{
	int arcs[MAXSIZE][MAXSIZE];
	int nodenum;
}MGraph,*PMGraph;

void Floyd(MGraph g,FILE *fp);
void Init_MGraph(PMGraph pg,FILE *fp);

int main()
{
	fp = fopen("input.dat","r");
	MGraph g;
	Init_MGraph(&g,fp);
	Floyd(g,fp);
	getchar();
	getchar();
	fclose(fp);
	return 0;
}

void Floyd(MGraph g,FILE *fp)
{
	int tests;
	fscanf(fp,"%d",&tests);
	int path[MAXSIZE][MAXSIZE][MAXSIZE];
	int distance[MAXSIZE][MAXSIZE];
	for(int i=0; i<g.nodenum; i++){
		for(int j=0; j<g.nodenum; j++){
			distance[i][j] = g.arcs[i][j];
			for(int k=0; k<g.nodenum; k++)path[i][j][k] = 0;
			if(distance[i][j] < INF){
				path[i][j][i] = 1;
				path[i][j][j] = 1;
			}
		}
	}
	for(int i=0; i<g.nodenum; i++){
		for(int j=0; j<g.nodenum; j++){
			for(int k=0; k<g.nodenum; k++){
				if(distance[j][k] > distance[j][i] + distance[i][k]){
					distance[j][k] = distance[j][i] + distance[i][k];
					for(int t=0; t<g.nodenum; t++)
						path[j][k][t] = path[j][i][t]||path[i][k][t];
				}
			}
		}
	}
	for(int i=0; i<tests; i++){
		int start,end;
		fscanf(fp,"%d%d",&start,&end);
		cout<<distance[start][end]<<endl;
		for(int i=0; i<g.nodenum; i++)
			if(path[start][end][i])cout<<i<<"-->";
		for(int i=0; i<g.nodenum; i++)
			if(path[end][start][i])cout<<i<<"-->";
		cout<<endl;
	}
}

void Init_MGraph(PMGraph pg,FILE *fp)
{
	int n;
	fscanf(fp,"%d",&n);
	pg->nodenum = n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			fscanf(fp,"%d",&pg->arcs[i][j]);
	}
}

/*
void floyd (Graph *pgraph, ShortPath *ppath)
{	int 	i, j, k;
	for (i=0; i<pgraph->vexCount; i++)
	      for (j=0; j<pgraph->vexCount; j++)
	      {	if (pgraph->arcs[i][j]!=MAX)  
			ppath->nextvex[i][j]=j;
		else ppath->nextvex[i][j]= -1;
			ppath->a[i][j]=pgraph->arcs[i][j];
	      }
	for (k=0; k<pgraph->vexCount; k++)
	      for (i=0; i<pgraph->vexCount; i++)
		for (j=0; j<pgraph->vexCount; j++)
		{    if ( (ppath->a[i][k]>=MAX) || (ppath->a[k][j]>=MAX) )
    				continue;
		      if (ppath->a[i][j]>(ppath->a[i][k]+ ppath->a[k][j]) )
		     {	ppath->a[i][j]= ppath->a[i][k]+ ppath->a[k][j];
			ppath->nextvex[i][j]=ppath->nextvex[i][k];
		     }
		}
}
*/