#include "stdio.h"  
int main()  
{  
        double pi=2;  
        int i;  
        for(i=1000;i>=1;i--)  
                pi=pi*(float)i/(2*i+1)+2;  
        printf("%f\n",pi);  
        getchar();  
        return 0;
}  