#include <stdio.h>
#include <string.h>

#define maxSize 1010
#define maxCnt  200000000

void mul(int *nomi, int nume) 					//乘以分子，大数乘法
{
	int i;
	int curD, remD;
	remD = 0;
	for(i=maxSize-1; i>0; i--){
		curD    = nomi[i] * nume + remD;
		nomi[i] = curD % 10;
		remD    = curD / 10;
	}
}

void div(int *nomi, int deno)					//除以分母，大数除法
{
	int i;
	int curD, remD;
	remD = 0;
	for(i=0; i<maxSize; i++)
	{
		curD    = nomi[i] + remD * 10;
		nomi[i] = curD / deno;
		remD    = curD % deno;
	}
}

int add(int *nomi, int *res)					//把当前项加到结果上，大数加法
{
	int i;
	int curD, remD;
	int Run = 0;								
	for(i=maxSize-1; i>0; i--)
	{
		curD     = res[i] + nomi[i];
		res[i]   = curD % 10;
		res[i-1]+= curD / 10;
		Run     |= nomi[i];
	}
	return Run;
}

void solve(int printDigit)
{
	int i;
	int res[maxSize];							//res[]   保存结果        (result)
	int nomi[maxSize];							//mi[]  保存当前项结果  (nomial)
	int nume=1;									//nume    保存分子        (numerator)
	int deno=3;									//deno    保存分母        (denominator)
	int Run=1;									//Run     用来判断，如果当前项每个位数上都是0，则结束
	int cnt=0;									//cnt     记录展开项的项数

	memset( res,0,sizeof(res) );				//memset  函数，将数组内全部用 0 填充
	memset(nomi,0,sizeof(nomi));
	 res[1] = 2;
	nomi[1] = 2;

	while(Run && (++cnt<maxCnt))
	{
		mul(nomi, nume);
		div(nomi, deno);
		Run = add(nomi, res);
		nume++;
		deno+=2;
	}

	printf("3.");
	for(i=2; i<printDigit+2; i++)
		printf("%d", res[i]);
	printf("\n");
}

int main()
{
	int printDigit;
	scanf("%d", &printDigit);
	solve(printDigit);
	getchar();
	getchar();
	return 0;
}