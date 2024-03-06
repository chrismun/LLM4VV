#include "acc_testsuite.h"

#define N 100

int test1(){
    int err = 0;
    int i;
    int *data = (int*)malloc(N * sizeof(int));

    for(i = 0; i < N; i++) {
        data[i] = 0;
    }

    #pragma acc data copy(data[0:N])
    {
        #pragma acc parallel loop
        for(i = 0; i < N; i++) {
            #pragma acc atomic update
            data[i]++;
        }
    }

    for(i = 0; i < N; i++) {
        if(data[i] != 1) {
            err++;
        }
    }

    free(data);

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