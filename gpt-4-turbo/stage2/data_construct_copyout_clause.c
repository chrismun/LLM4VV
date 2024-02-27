#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Assuming SEED and NUM_TEST_CALLS would be defined in your testing environment or header files.
#define SEED 1234
#define NUM_TEST_CALLS 10

// This simple test checks if the copyout clause correctly copies data from the device back to the host
int test1(){
    int err = 0;
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    
    // Initialize array on host
    for(int i = 0; i < size; i++){
        a[i] = i;
    }

    // Using OpenACC parallel region to modify the array
    #pragma acc parallel loop copyout(a[0:size])
    for(int i = 0; i < size; i++){
        a[i] += 1;
    }

    // Verification
    for(int i = 0; i < size; i++){
        if(a[i] != i + 1){
            err++;
            break;
        }
    }

    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    
    if(failcode == 0)
        printf("Test passed.\n");
    else
        printf("Test failed with code %d.\n", failcode);
    
    return failcode;
}