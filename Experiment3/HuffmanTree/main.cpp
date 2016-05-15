#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define INF 10000
#define MAXSIZE 100
using namespace std;
FILE *fp;
typedef struct HTNode
{
	int weight;
	int father,lch,rch;
}HTNode,*PHTNode;

typedef struct HTree
{
	HTNode htree[MAXSIZE];
	int root;
}HTree,*PHTree;

int HTree_Init(PHTree *ppht,int *weight,int num);
int Find_2_Min(HTree ht,int *min,int *lessmin,int stop);
int Solve_Code(HTree ht,char *str,char *chs,int);

int main()
{
	fp = fopen("input.dat","r");
    PHTree pht;
    int num;
    fscanf(fp,"%d",&num);
    char chs[MAXSIZE];
    char str[MAXSIZE];
    int weight[MAXSIZE];
    for(int i=0; i<num; i++){
        fscanf(fp,"%c",&chs[i]);
        if(chs[i]==' ')i--;//字符文件输入时处理空格
    }

    for(int i=0; i<num; i++)
        fscanf(fp,"%d",&weight[i]);
    //getchar();
    gets(str);

    HTree_Init(&pht,weight,num);
    Solve_Code(*pht,str,chs,num);
    getchar();
    getchar();
    fclose(fp);
    return 0;
}

int HTree_Init(PHTree *ppht,int *weight,int num)
{
    int min,lessmin;
	(*ppht) = (PHTree)malloc(sizeof(HTree));
    for(int i=0; i<2*num-1; i++){
        (*ppht)->htree[i].father = (*ppht)->htree[i].lch = (*ppht)->htree[i].rch = -1;
        if(i<num)
            (*ppht)->htree[i].weight = weight[i];
        else
            (*ppht)->htree[i].weight = 0;
    }
    for(int i=0; i<num-1; i++){
        Find_2_Min(**ppht,&min,&lessmin,num+i);
        (*ppht)->htree[min].father = (*ppht)->htree[lessmin].father = num+i;
        (*ppht)->htree[num+i].lch = min;
        (*ppht)->htree[num+i].rch = lessmin;
        (*ppht)->htree[num+i].weight = (*ppht)->htree[lessmin].weight+(*ppht)->htree[min].weight;
        (*ppht)->root = num+i;
    }
    return 1;
}

int Find_2_Min(HTree ht,int *min,int *lessmin,int stop)
{
    int pre,cur;//cur比pre小
    pre = cur = INF;
    for(int i=0; i<stop; i++){
        if(ht.htree[i].weight < cur && ht.htree[i].father == -1){
            pre = cur;
            cur = ht.htree[i].weight;
            int temp=*min;
            *lessmin = *min;
            *min = i;
        }
        else if(ht.htree[i].weight < pre && ht.htree[i].father == -1){
            pre = ht.htree[i].weight;
            *lessmin = i;
        }
    }
    return 1;
}

int Solve_Code(HTree ht,char *str,char *chs,int num)
{
    for(int i=0; i<strlen(str); i++){
        int pos;
        for(int j=0; j<num; j++)
            if(chs[j] == str[i])pos=j;
        char codes[MAXSIZE];
        int child = pos,cnt=0;
        int father = ht.htree[pos].father;
        while(ht.htree[child].father != -1){
            if(child == ht.htree[father].lch)
                codes[cnt++] = '1';
            else if(child == ht.htree[father].rch)
                codes[cnt++] = '0';
            child = father;
            father = ht.htree[father].father;
        }
        while(--cnt){
            cout<<codes[cnt];
        }
        cout<<codes[0]<<"  ";
    }
    return 1;
}
