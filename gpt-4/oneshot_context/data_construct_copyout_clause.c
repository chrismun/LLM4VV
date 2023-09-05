#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main()
{
    int *a = (int*) malloc(sizeof(int)*N);
    int i;

    #pragma acc data copyout(a[0:N])
    {
        #pragma acc parallel loop
        for(i=0; i<N; i++) {
            a[i] = i*i;
        }
    }

    for(i=0; i<N; i++) {
        printf("a[%d] = %d\n", i, a[i]);
    }

    free(a);

    return 0;