#include <stdio.h>
#include <stdlib.h>

// Assuming definitions for acc_testsuite.h
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size], b[size];
    int scalar = 2;

    // Initialize arrays
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Using parallel loop combined construct to multiply array a[] elements by scalar and store in b[]
    #pragma acc parallel loop
    for(int i = 0; i < size; ++i){
        b[i] = a[i] * scalar;
    }

    // Verifying the results
    for(int i = 0; i < size; ++i){
        if(b[i] != a[i]*scalar){
            err++;
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
    return failcode;
}