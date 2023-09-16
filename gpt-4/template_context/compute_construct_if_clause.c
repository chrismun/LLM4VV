#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main()
{
    #ifdef _OPENACC
        printf("OpenACC is supported, version: %d\n", _OPENACC);
    #else
        printf("OpenACC is not supported.\n");
        return -1;
    #endif

    float *a, *b, *c;
    int n = 1<<20;
    a = (float*)malloc(n*sizeof(float));
    b = (float*)malloc(n*sizeof(float));
    c = (float*)malloc(n*sizeof(float));

    for(int i = 0; i < n; i++){
        a[i] = i;
        b[i] = i;
    }

    #pragma acc parallel copyin(a[0:n],b[0:n]) copyout(c[0:n]) 
    {
        #pragma acc loop 
        for(int i=0; i<n; i++){
            c[i] = a[i] + b[i];
        }
    }

    float sum = 0;
    for(int i = 0; i < n; i++)
        sum += c[i];

    printf("Expected: %f\n", 3 * (n-1) / 2.0);
    printf("Got: %f\n", sum / n);

    return 0;
}