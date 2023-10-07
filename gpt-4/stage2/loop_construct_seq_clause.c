#include "acc_testsuite.h"
#ifndef T1
#define N 1024
/*T1:loop construct seq clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* a = (int*)malloc(sizeof(int)*N);

    #pragma acc parallel copy(a[0:N])
    {
        #pragma acc loop seq
        for(int i=0; i<N; i++){
            a[i] = i;
        }
    }

    for(int i=0; i<N; i++){
        if(a[i] != i){
            err = 1;
            break;
        }
    }

    free(a);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}