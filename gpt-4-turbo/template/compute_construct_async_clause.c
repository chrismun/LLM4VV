#include "acc_testsuite.h"
#ifndef T1
//T1:compute,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024; // Size of data arrays
    int *a, *b, *c;
    a = (int*)malloc(sizeof(int) * size);
    b = (int*)malloc(sizeof(int) * size);
    c = (int*)malloc(sizeof(int) * size);

    // Initialize arrays
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform operations asynchronously
    #pragma acc kernels async(1) copyin(a[0:size], b[0:size]) copyout(c[0:size])
    for(int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }

    #pragma acc kernels async(2) copyin(c[0:size]) copy(c[0:size])
    for(int i = 0; i < size; ++i) {
        c[i] = c[i] * 2;
    }

    // Since operations are asynchronous, we need to wait before verifying results
    #pragma acc wait(2)

    // Verify the results
    for(int i = 0; i < size; ++i) {
        if(c[i] != 2 * (a[i] + b[i])) {
            err++;
        }
    }

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