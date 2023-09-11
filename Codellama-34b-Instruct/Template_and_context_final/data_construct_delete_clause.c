#include "acc_testsuite.h"

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* a = (int*)malloc(sizeof(int));
    int* b = (int*)malloc(sizeof(int));
    int* c = (int*)malloc(sizeof(int));

    // Initialize the pointers
    *a = 1;
    *b = 2;
    *c = 3;

    // Create a data construct with the delete clause
    #pragma acc data delete(a, b, c)
    {
        // Do some work with the data
        #pragma acc parallel
        {
            // Increment the values of a, b, and c
            a[0] += 1;
            b[0] += 2;
            c[0] += 3;
        }
    }

    // Check that the values of a, b, and c have been deleted
    if (*a != 0 || *b != 0 || *c != 0) {
        err = 1;
    }

    // Free the memory
    free(a);
    free(b);
    free(c);

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