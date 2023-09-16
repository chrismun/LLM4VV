#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define N 100000

void test()
{
    float* a;

    a = (float*) acc_malloc(N * sizeof(float));

    assert(a != NULL);

    #pragma acc parallel loop present(a)
    for(int i = 0; i < N; i++) {
        a[i] = (float)i;
    }

    #pragma acc exit data delete(a[0:N])

    acc_free(a);

    printf("Test passed.\n");
}

int main()
{
    test();
    return 0;
}