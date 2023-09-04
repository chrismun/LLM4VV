#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Scenario 1: Private variables are created for each thread in vector-partitioned mode.
    int n = 100;
    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));
    int* c = (int*)malloc(n * sizeof(int));
    int* tmp = (int*)malloc(n * sizeof(int));
    int* result = (int*)malloc(n * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
        tmp[i] = 0;
        result[i] = 0;
    }

    // Run loop in vector-partitioned mode
    #pragma acc parallel loop gang(static:1) vector(length:n) private(tmp)
    for (int i = 0; i < n; i++) {
        tmp[i] = b[i] + c[i];
        #pragma acc loop vector
        for (int j = 0; j < n; j++) {
            result[i] += tmp[j];
        }
    }

    // Check results
    for (int i = 0; i < n; i++) {
        if (result[i] != (a[i] + b[i] + c[i])) {
            err = 1;
            break;
        }
    }

    // Scenario 2: Private variables are created for each worker and shared across all vector lanes of a worker in worker-partitioned vector-single mode.
    n = 100;
    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (int*)malloc(n * sizeof(int));
    tmp = (int*)malloc(n * sizeof(int));
    result = (int*)malloc(n * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
        tmp[i] = 0;
        result[i] = 0;
    }

    // Run loop in worker-partitioned vector-single mode
    #pragma acc parallel loop gang(static:1) worker(static:1) vector(length:n) private(tmp)
    for (int i = 0; i < n; i++) {
        tmp[i] = b[i] + c[i];
        #pragma acc loop vector
        for (int j = 0; j < n; j++) {
            result[i] += tmp[j];
        }
    }

    // Check results
    for (int i = 0; i < n; i++) {
        if (result[i] != (a[i] + b[i] + c[i])) {
            err = 1;
            break;
        }
    }

    // Scenario 3: Private variables are created for each gang in all dimensions and shared across all threads associated with all vector lanes of all workers of that gang.
    n = 100;
    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (int*)malloc(n * sizeof(int));
    tmp = (int*)malloc(n * sizeof(int));
    result = (int*)malloc(n * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
        tmp[i] = 0;
        result[i] = 0;
    }

    // Run loop in gang-partitioned mode
    #pragma acc parallel loop gang(static:1) vector(length:n) private(tmp)
    for (int i = 0; i < n; i++) {
        tmp[i] = b[i] + c[i];
        #pragma acc loop vector
        for (int j = 0; j < n; j++) {
            result[i] += tmp[j];
        }
    }

    // Check results
    for (int i = 0; i < n; i++) {
        if (result[i] != (a[i] + b[i] + c[i])) {
            err = 1;
            break;
        }
    }

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