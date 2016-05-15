#include <cstdio>
#include <cstdlib>
#include <iostream>
#define INF 10000
#define MaxVex 100
#define TRUE 1
#define FALSE 0
using namespace std;



typedef struct {
	int  arcs[MaxVex][MaxVex];
	int vexnum,arcnum;
}MGraph;

void ShorPath(MGraph G,int *D,int ,int);

int main()
{
	MGraph Graph;
	FILE *fp;
	fp = fopen("input.dat","r");
	int D[MaxVex];
	int vexnum,egnum;
	fscanf(fp,"%d%d",&vexnum,&egnum);
	//cin>>n;
	Graph.vexnum = vexnum;
	Graph.arcnum = egnum;
	for(int i=0;i<vexnum;i++){
		for(int j=0; j<vexnum; j++)Graph.arcs[i][j]=10000;
	}
	for(int i=0; i<vexnum; i++)
		for(int j=0; j<vexnum; j++)
			if(j==i)Graph.arcs[i][j]=0;
	for(int i=0;i<egnum;i++){
		int x,y,z;
		fscanf(fp,"%d%d%d",&x,&y,&z);
		//cin>>x>>y>>z;
		Graph.arcs[x-1][y-1] = z;
	}
	int start,end;
	fscanf(fp,"%d%d",&start,&end);
	//cin>>vcnt;
	ShorPath(Graph,D,start-1,end-1);
	//for(int i=0;i<n;i++)cout<<D[i]<<' ';
	getchar();
	getchar();
	fclose(fp);
	return 0;
}



void ShorPath(MGraph G,int *D,int v0,int vend)
{
	int final[G.vexnum];
	int P[MaxVex][MaxVex];
	int v,w;
	for(v=0;v<G.vexnum;v++){
		final[v] = FALSE;
		D[v] = G.arcs[v0][v];
		for(w=0;w<G.vexnum;w++){
			P[v][w] = FALSE;
		}
		if(D[v]<INF){
			P[v][v0] = TRUE;
			P[v][v] = TRUE;
		}
	}
	D[v0] = 0;
	final[v0] = TRUE;
	for(int i=0;i<G.vexnum;i++){
		int mi=INF;
		for(w=0;w<G.vexnum;w++){
			if(!final[w]){
				if(D[w]<mi){
					v = w;
					mi = D[w];
				}
			}
		}
		final[v] = TRUE;
		for(w=0;w<G.vexnum;w++){
			if(!final[w] && mi+G.arcs[v][w]<D[w]){
				D[w] = mi + G.arcs[v][w];
				//P[w] = P[v];
				for(int i=0;i<G.vexnum;i++)P[w][i] = P[v][i];
				P[w][w] = TRUE;
			}
		}
	}
	/*
	if(v0<=vend){
		for(int i=0;i<G.vexnum;i++){
			if(P[vend][i])cout<<i<<endl;
		}
	}
	else{
		for(int i=G.vexnum-1;i>=0;i--){
			if(P[vend][i])cout<<i<<endl;
		}
	}
	*/
	cout<<D[vend]<<endl;
}