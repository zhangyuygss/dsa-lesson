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
	int n;
	fscanf(fp,"%d",&n);
	//cin>>n;
	Graph.vexnum = n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			fscanf(fp,"%d",&(Graph.arcs[i][j]));
			//cin>>Graph.arcs[i][j];
		}
	}
	int v0,v,cnt;
	fscanf(fp,"%d",&cnt);
	//cin>>vcnt;
	for(int t=0;t<cnt;t++){
		fscanf(fp,"%d%d",&v0,&v);
		ShorPath(Graph,D,v0,v);
	}

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