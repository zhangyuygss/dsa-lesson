#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAXSIZE 11
using namespace std;

typedef struct HashTable
{
	int table[MAXSIZE];
	int num;
}HashTable,*PHashTable;

int Search_HTable(PHashTable pht,int key,int *pos,int *searchcnt);
int Insert_HTable(PHashTable pht,int *searchcnt,int key);
int Hash(int key);
int Confict(int key,int searchcnt);

int main()
{
	FILE *fp;
	fp = fopen("input.dat","r");
	HashTable ht;
	int num;
	fscanf(fp,"%d",&num);
	int keys[MAXSIZE],secnt[MAXSIZE];//secnt表示查找次数，key为数据原始数组
	for(int i=0; i<num; i++)secnt[i]=0;
	for(int i=0; i<num; i++){
		fscanf(fp,"%d",&keys[i]);
		Insert_HTable(&ht,&secnt[i],keys[i]);
	}
	int allsearchtime=0;
	cout<<num<<endl;
	for(int i=0; i<num; i++){
		cout<<secnt[i]<<endl;
		allsearchtime+=secnt[i];
	}
	cout<<"ASL:"<<float(allsearchtime/num)<<endl;
	getchar();
	getchar();
}

int Hash(int key)
{
	return (key*3)/MAXSIZE;
}

int Confict(int key,int searchcnt)
{
	return searchcnt*((7*key)%MAXSIZE);
}

int Search_HTable(PHashTable pht,int key,int *pos,int *searchcnt)
{
	int curpos =Hash(key);
	*pos = curpos;
	*searchcnt = 1;
	while(curpos<MAXSIZE && pht->table[curpos]!=-1 && pht->table[curpos]!=key){
		curpos = Confict(key,*searchcnt);
		*pos = curpos;
		*searchcnt += 1;
		if(*searchcnt >=MAXSIZE){
			cout<<"Conflic too Much in key:"<<key<<endl;
			return -1;
		}
	}
	if(pht->table[curpos]==key)return 1;
	else if(curpos >= MAXSIZE){
		cout<<"Out of table in key:"<<key<<endl;
		return -2;
	}
	else return 0;
}

int Insert_HTable(PHashTable pht,int *searchcnt,int key)
{
	int pos;
	if(Search_HTable(pht,key,&pos,searchcnt))return 0;
	else{
		pht->table[pos] = key;
		pht->num++;
		return 1;
	}
}

