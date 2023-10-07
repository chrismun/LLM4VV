#include "acc_testsuite.h"
#ifndef T1
#define N 1000000
int test1(){
    int err = 0;
    srand(SEED);
    float *a = (float*) malloc(sizeof(float)*N);
    float *b = (float*) malloc(sizeof(float)*N);

    for(int i = 0; i<N; i++) {
        a[i] = rand();
        b[i] = a[i];
    }

    acc_init(acc_device_default);
    
    int async = acc_async_test_all();
    if(async != 0){ // If any operations are still computing, it returns non-zero.
        err = 1;
    }
    
    #pragma acc enter data copyin(a[0:N]) async(1)
    #pragma acc enter data copyin(b[0:N]) async(2)
    while(acc_async_test(1) == 0);
    while(acc_async_test(2) == 0);

    #pragma acc parallel loop present(a[0:N], b[0:N]) async(1)
    for(int i=0; i<N; i++) {
        a[i] += b[i];
    }
    
    while(acc_async_test(1) == 0);
    if(acc_async_test(1) != 0) { // If the operation is not completed, it returns non-zero.
        err = 1;
    }

    #pragma acc exit data copyout(a[0:N]) delete(b[0:N]) async(1)
    while(acc_async_test(1) == 0);
    
    if(acc_async_test(1) != 0) { // If the operation is not completed, it returns non-zero.
        err = 1;
    } 

    free(a);
    free(b);
    acc_shutdown(acc_device_default);
    
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