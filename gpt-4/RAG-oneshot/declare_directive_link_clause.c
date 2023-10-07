#include <stdio.h>
#include <openacc.h>
#define N 1024

float a[N], b[N], c[N];

#pragma acc declare link(a, b, c)

void vec_add()
{
    #pragma acc parallel loop
    for(int i=0; i<N; i++)
    {
        c[i] = a[i] + b[i];
    }
}

int main()
{
    for (int i=0; i<N; i++)
    {
        a[i] = i;
        b[i] = i * 1000;
        c[i] = 0.0f;
    }
    #pragma acc enter data copyin(a[:N], b[:N]) create(c[:N])
    vec_add();
    #pragma acc exit data copyout(c[:N])
    for (int i=0; i<N; i++)
    {
        if(c[i] != a[i] + b[i]) // check if the vector addition is done correctly
        {
            printf("Test failed at index %d. Result is %f\n", i, c[i]);
            return -1;
        }
    }
    printf("Declare Directive Link Clause Test: PASS\n");
    return 0;
}