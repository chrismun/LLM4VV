#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int main(){
    int a[SIZE];
    int flag = 1;

    for(int i=0;i<SIZE;i++)
        a[i]=i;

    #pragma acc kernels if(flag) 
    {
        for(int i=0;i<SIZE;i++)
            a[i] = a[i] * a[i];
    }

    printf("Result:");
    for (int i=0;i<SIZE;i++)
        printf("%d ",a[i]);

    return 0;
}