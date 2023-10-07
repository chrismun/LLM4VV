#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int N = 100;
    int *data;
    
    data = (int *)malloc(N * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        err = 1;
    }
    
    // Initialize data
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }
    
    #pragma acc data create(data[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            data[i] *= 2;
        }
    }
    
    // Verify result
    for (int i = 0; i < N; i++) {
        if (data[i] != 2*i) {
            printf("Data validation failed.\n");
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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}