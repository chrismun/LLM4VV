#include "acc_testsuite.h"
#define SIZE 100 // you can change SIZE according to your needs

// Test Function
int test1(){
    int err = 0;
    srand(SEED);
    int a[SIZE];
    int b[SIZE];
    int c[SIZE];
    int c_verify[SIZE];

    // Initialize arrays a and b
    for(int i = 0; i < SIZE; i++){
        a[i] = rand() % 50;
        b[i] = rand() % 50;
    }

    // Sequential calculation for verification
    for(int i = 0; i < SIZE; i++){
        c_verify[i] = a[i] + b[i];
    }

    // Parallel execution using OpenACC
    #pragma acc parallel loop independent
    for(int i = 0; i < SIZE; i++){
        c[i] = a[i] + b[i];
    }

    // Check for any error
    for(int i = 0; i < SIZE; i++){
        if(c[i] != c_verify[i]){
            err = 1;
            break;
        }
    }

    return err;
}

// Main driver function
int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}