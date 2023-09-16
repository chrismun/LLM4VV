#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int length = 64;
    int err = 0;
    unsigned int* a = (unsigned int*)malloc(length * sizeof(unsigned int));
    unsigned int* b = (unsigned int*)malloc(length * sizeof(unsigned int));
    srand(SEED);
    for(int i=0; i<length; i++){
        a[i] = rand()%length;
        b[i] = 0;
    }

    #pragma acc parallel num_workers(32) copyin(a[0:length]) copyout(b[0:length])
    {
        #pragma acc loop worker
        for(int i=0; i<length; i++){
            b[i] = a[i];
        }
    }

    for(int i=0; i<length; i++){
        if(b[i] != a[i]){
            err = 1;
        }
    }

    free(a);
    free(b);

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