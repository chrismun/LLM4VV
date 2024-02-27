#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h> // Include the OpenACC header

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:data construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));
    bool is_correct = true;

    // Initialize arrays
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    // Test the data construct with the copy clause
    #pragma acc data copy(a[0:size]) copyout(b[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            b[i] = a[i] + 1; // Simple operation to verify the copy and copyout actions
        }
    }

    // Verify the results
    for (int i = 0; i < size; ++i) {
        if (b[i] != a[i] + 1) {
            is_correct = false;
            break;
        }
    }

    if(!is_correct) {
        err = 1; // Error: Data manipulation did not occur as expected
    }

    free(a);
    free(b);
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
    if (failcode == 0) {
        printf("PASS: OpenACC data construct is working properly.\n");
    } else {
        printf("FAIL: OpenACC data construct test failed. Error code: %d\n", failcode);
    }
    return failcode;
}