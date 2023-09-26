#include "acc_testsuite.h"

int test1(){
    int err = 0;
    srand(SEED);
    
    float a[100], b[100], c[100], result[100];
    int i;

    // Initialize variables
    for(i=0; i<100; i++){
        a[i]=1.0f;
        b[i]=2.0f;
    }

    #pragma acc kernels 
    for(i=0; i<100; i++){
        result[i] = a[i] + b[i];
    }

    // Check Results
    for(i=0; i<100; i++){
        if(result[i] != 3.0f){
            err = 1;
            break;
        }
    }

    return err;
}

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

    if(failcode == 0){
        printf("Test Passed \n");
    }else{
        printf("Test Failed \n");
    }

    return failcode;
}