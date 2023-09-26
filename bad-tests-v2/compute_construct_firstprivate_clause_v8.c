#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define N 256

int test_firstprivate(){
    int i;
    int err = 0;
    int *a, *b;

    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));

    for(i = 0; i < N; i++){
        a[i] = i;
        b[i] = -1;
    }

    #pragma acc data copy(a[0:N], b[0:N])
    {
        #pragma acc parallel num_gangs(N) firstprivate(a[0:N])
        {
            int idx = acc_gang_id();
            b[idx] = a[idx];
        }
    }

    for(i = 0; i < N; i++){
        if(b[i] != i){
            err++;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int i;
    int err = 0;

    for(i = 0; i < 5; i++){
        err += test_firstprivate();
    }

    if(err == 0){
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }

    return 0;
}