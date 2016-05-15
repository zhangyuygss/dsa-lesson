#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAXSIZE 1000
using namespace std;

int main()
{
	int a[2][4]={'a'};
	for(int i=0; i<2; i++)
		for(int j=0; j<4; j++)
			cout<<a[i][j]<<endl;
	getchar();
	getchar();
	return 0;
}