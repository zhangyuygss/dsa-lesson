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

void ShorPath(MGraph G,int *D);

int main(){
	MGraph Graph;

	int D[MaxVex];
	int n;
	cin>>n;
	Graph.vexnum = n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			cin>>Graph.arcs[i][j];
	}
	ShorPath(Graph,D);
	for(int i=0;i<n;i++)cout<<D[i]<<' ';
	return 0;
}



void ShorPath(MGraph G,int *D){
	int final[G.vexnum];
	int P[MaxVex][MaxVex];
	int v,w;
	for(v=0;v<G.vexnum;v++){
		final[v] = FALSE;
		D[v] = G.arcs[0][v];
		for(w=0;w<G.vexnum;w++){
			P[v][w] = FALSE;
		}
		if(D[v]<INF){
			P[v][0] = TRUE;
			P[v][v] = TRUE;
		}
	}
	D[0] = 0;
	final[0] = TRUE;
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
				P[w] = P[v];
				P[w][w] = TRUE;
			}
		}
	}
}












