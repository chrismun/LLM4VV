#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SIZE 10000
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    float* a = (float*)malloc(sizeof(float)*SIZE);
    float* b = (float*)malloc(sizeof(float)*SIZE);
    float* res = (float*)malloc(sizeof(float)*SIZE);

    // Fill 'a' and 'b' arrays
    for(int i=0; i<SIZE; i++){
        a[i] = (float)i;
        b[i] = (float)i;
    }

    #pragma acc kernels copy(a[0:SIZE],b[0:SIZE],res[0:SIZE])
    {
        for(int i=0; i<SIZE; i++){
            res[i] = a[i]+b[i];
        }
    }

    // Check output
    for(int i=0; i<SIZE; i++){
        if(res[i] != a[i]+b[i]){
            err = 1;
        }
    }

    free(a);
    free(b);
    free(res);

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    printf("Test %s\n", failcode ? "Failed!" : "Passed!");

    return failcode;
}