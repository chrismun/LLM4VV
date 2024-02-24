#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_TEST_CALLS 100

int test1(){
    int err = 0;
    int *a = (int*)malloc(100 * sizeof(int));

    #pragma omp parallel for
    for(int i = 0; i < 100; i++) {
        a[i] = i;
    }

    #pragma omp parallel for
    for(int i = 0; i < 100; i++) {
        if(a[i] != i) {
            err = 1;
        }
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            free(a);
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}