#include "acc_testsuite.h"
#ifndef T1
//T1:data construct create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int size = 100;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));
    int *c = (int*)malloc(size * sizeof(int));

    // Initialize arrays
    for(int i = 0; i < size; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = rand() % 100;
    }

    // Use data construct with create clause
    #pragma acc data copyin(a[0:size], b[0:size]) create(c[0:size])
    {
        for(int i = 0; i < size; i++){
            c[i] = a[i] + b[i];
        }
    }

    // Verify the result
    for(int i = 0; i < size; i++){
        if(c[i] != a[i] + b[i]){
            err = 1;
            break;
        }
    }

    // Free memory
    free(a);
    free(b);
    free(c);

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