#include "acc_testsuite.h"

//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    int* a = (int*)malloc(sizeof(int)*N);

    srand(SEED);
    for(int i=0; i<N; ++i)
        a[i] = rand();

    #pragma acc enter data copyin(a[0:N])
    #pragma acc parallel loop
    for(int i=0; i<N; ++i)
        a[i] += 1;
    #pragma acc exit data copyout(a[0:N])

    // check if array a was properly updated on the accelerator
    for(int i=0; i<N; ++i){
        if(a[i] != (i+1+SEED)%N){
            err = 1;
            break;
        }
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}