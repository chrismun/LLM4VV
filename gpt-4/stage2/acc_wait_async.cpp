#include "acc_testsuite.h"

#ifndef T1
/*T1:acc wait async,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *data = (int*) malloc(1000*sizeof(int));

    // Launch 1000 async copy tasks
    for (int i = 0; i < 1000; ++i){
        data[i] = i;
        acc_async_copy(data + i, data + i, sizeof(int));
    }

    // Wait for all async operations to finish
    acc_wait_async(1000, 0);

    // Verify the data 
    for (int i = 0; i < 1000; ++i){
        if (data[i] != i) {
            err = 1;
            break;
        }
    }

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
        failed += test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}