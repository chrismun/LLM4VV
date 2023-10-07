#include "acc_testsuite.h"

#ifndef T1
/*T1:parallel construct async clause,V:2.0-2.7*/

int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int*)malloc(SIZE*sizeof(int));
    for(int i=0; i<SIZE; i++) data[i]=i;

    #pragma acc parallel loop async(1)
    for(int i=0; i<SIZE; i++)
        data[i] += i;

    #pragma acc parallel loop async(2)
    for(int i=0; i<SIZE; i++)
        data[i] -= 2*i;

    #pragma acc wait

    for(int i=0; i<SIZE; i++)
        if(data[i] != -i) err = 1;

    free(data);
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