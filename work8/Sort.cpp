#include <cstdlib>
#include <cstdio>
#include <iostream>
#define MAXSIZE 110
using namespace std;

int Insert_Sort(int *numbers,int num);

int main()
{
	FILE *fp;
	fp = fopen("input.dat","r");
	int numbers[MAXSIZE]={0};
	int num;
	fscanf(fp,"%d",&num);
	for(int i=1; i<=num; i++)
		fscanf(fp,"%d",&numbers[i]);
	Insert_Sort(numbers,num);
	for(int i=1; i<num; i++)
		cout<<numbers[i]<<" ";
	cout<<endl;
	getchar();
	getchar();
	fclose(fp);
	return 0;
}

int Insert_Sort(int *numbers,int num)
{
	for(int i=2; i<=num; i++){
		numbers[0] = numbers[i];
		int low=1,high=i-1;
		while(low<=high){
			if(numbers[(low+high)/2] < numbers[0])
				low = (low+high)/2 +1;
			else
				high = (low+high)/2 -1;
		}
		for(int j=i-1; j>high; j--){
			numbers[j+1] = numbers[j];
		}
		numbers[high+1] = numbers[0];
	}
}
