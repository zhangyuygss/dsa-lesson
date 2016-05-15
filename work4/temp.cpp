#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

int main()
{
	int n,k;
	cin>>n;
	int str[100];
	for(int i=0;i<n;i++)cin>>str[i];
	cin>>k;
	for (int i = n-k; i < n; ++i)
	{
		cout<<str[i]<<endl;
	}
	for (int i = 0; i < n-k; ++i)
	{
		cout<<str[i]<<endl;
	}
	getchar();
	getchar();
	return 0;
}