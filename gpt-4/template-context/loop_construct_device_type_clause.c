#include "openacc.h"
#include "acc_testsuite.h"
#include <stdlib.h>

int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data arrays
    const int N = 100;
    float a[N], b[N], c[N];

    // Populate 'a' and 'b' arrays
    for(int i = 0; i < N; i++){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
    }

    // OpenACC Parallel region start
    #pragma acc parallel num_gangs(1) vector_length(32)
    {
        #pragma acc loop gang worker vector
        for(int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    }
    // OpenACC Parallel region end

    // Check results
    for(int i = 0; i < N; i++){
        if(c[i] != a[i] + b[i]){
            err = 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Testing
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if(failed != 0){
        failcode += 1;
    }

    // Print Test Result
    if(failcode == 0){
        printf("OpenACC Compiler Test: PASSED \n");
    }
    else{
        printf("OpenACC Compiler Test: FAILED \n");
    }

    return failcode;
}