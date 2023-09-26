#include "acc_testsuite.h"
#ifndef T1
// T1:compute construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    int length = 100;
    srand(SEED);

    int* a = (int*)malloc(length*sizeof(int));

    for (int x = 0; x < length; ++x){
        a[x] = rand() % 100;
    }

    int first = a[0];

    #pragma acc data copy(a[0:length])
    {
        #pragma acc parallel loop firstprivate(first)
        for (int x = 0; x < length; ++x){
            if(a[x] != first){
                err = 1;
            }
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