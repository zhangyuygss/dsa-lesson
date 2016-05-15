#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAXSIZE 100
using namespace std;
FILE *fp;
typedef struct Trip
{
    int i,j,elem;// 行，列，值
}Trip;
typedef struct Matrix
{
    Trip data[MAXSIZE+1];//矩阵内容
    int rpos[MAXSIZE+1];//行逻辑数组
    int m,n,num;//行数，列数，非零元个数
}Matrix,*PMatrix;

int Init_Matrix(PMatrix *pmat,FILE *fp);
int Output_Matrix(Matrix mat);
int Add_Matrix2(PMatrix *pmatre ,Matrix mat1,Matrix mat2);

int main()
{
   fp = fopen("input.dat","r");
    PMatrix pmat1,pmat2,pmatre;
    Init_Matrix(&pmat1,fp);
    //Output_Matrix(*pmat1);
    Init_Matrix(&pmat2,fp);
    //Output_Matrix(*pmat2);
    Add_Matrix2(&pmatre,*pmat1,*pmat2);
    Output_Matrix(*pmatre);
    cout<<"------"<<endl;
    fclose(fp);
    getchar();
    getchar();
    return 0;
}

int Add_Matrix2(PMatrix *pmatre ,Matrix mat1,Matrix mat2)
{
    (*pmatre) = (PMatrix)malloc(sizeof(Matrix));
    if((*pmatre)){
        int m1[MAXSIZE][MAXSIZE] = {0};
        int m2[MAXSIZE][MAXSIZE] = {0};
        for(int p=1; p<=mat1.num; p++){
            m1[mat1.data[p].i][mat1.data[p].j] = mat1.data[p].elem;
        }
        for(int p=1; p<=mat2.num; p++){
            m2[mat2.data[p].i][mat2.data[p].j] = mat2.data[p].elem;
        }
        int m3[MAXSIZE][MAXSIZE]={0};
        //加
        for(int p=1; p<mat1.m; p++){
            for(int q=1; q<mat1.n; q++){
                m3[p][q] = m1[p][q] + m2[p][q];
            }
        }
        (*pmatre)->m = mat1.m;
        (*pmatre)->n = mat1.n;
        (*pmatre)->num = 0;
        for(int p=1; p<=mat1.m; p++){
            for(int q=1; q<=mat1.n; q++){
                if(m3[p][q]){
                    (*pmatre)->data[++((*pmatre)->num)].i = p;
                    (*pmatre)->data[((*pmatre)->num)].j = q;
                    (*pmatre)->data[((*pmatre)->num)].elem = m3[p][q];
                }
            }
        }
    }
    return 1;
}

int Output_Matrix(Matrix mat)
{
    for(int i=1; i<mat.num+1; i++){
        cout<<mat.data[i].i<<" "<<mat.data[i].j<<" "<<mat.data[i].elem<<endl;
    }
    cout<<"row:"<<mat.m<<" col:"<<mat.n<<" num:"<<mat.num<<endl;
    for(int i=1; i<=mat.m; i++)
        cout<<mat.rpos[i]<<"  ";
    cout<<endl;
    return 1;
}

int Init_Matrix(PMatrix *pmat,FILE *fp)
{//rpos的初始化要考虑没有出现的行的位置，向后对齐方便乘法
    (*pmat) = (PMatrix)malloc(sizeof(Matrix));
    if((*pmat)){
        int m,n;
         //cin>>m>>n;

        fscanf(fp,"%d%d",&m,&n);

        for(int i=1; i<=m; i++)
            (*pmat)->rpos[i] = 0;

        (*pmat)->m = m;
        (*pmat)->n = n;
        (*pmat)->num = 0;
        int ipre=0;//用于构建行逻辑数组
        while(1){
            int i,j,elem;//行，列，值
            fscanf(fp,"%d%d%d",&i,&j,&elem);
            //cin>>i>>j>>elem;
            if(!i)break;
            if(i != ipre){//构建行逻辑数组
                (*pmat)->rpos[i] = 1+(*pmat)->num;
                ipre = i;
            }
            (*pmat)->data[++((*pmat)->num)].i = i;//矩阵非零元个数加一
            (*pmat)->data[(*pmat)->num].j = j;
            (*pmat)->data[(*pmat)->num].elem = elem;
        }
    }
    if((*pmat)->rpos[(*pmat)->m]==0)
        (*pmat)->rpos[(*pmat)->m] =(*pmat)->num +1;
    for(int i=(*pmat)->m-1; i>=1; i--){
        if((*pmat)->rpos[i]==0)
            (*pmat)->rpos[i] = (*pmat)->rpos[i+1];
    }
    return 1;
}
