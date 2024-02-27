#include "acc_testsuite.h"
#ifndef T1
// T1:{loop},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 128;
    int *a = (int *)malloc(size * sizeof(int));
    int *b = (int *)malloc(size * sizeof(int));
    
    // Initialize array with random data and copy to a second array
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = a[i];
    }

    #pragma acc data copy(b[0:size])
    {
        #pragma acc parallel
        {
            // Using seq clause to enforce sequential execution
            #pragma acc loop seq
            for(int i = 1; i < size; ++i) {
                b[i] += b[i - 1];
            }
        }
    }

    // Sequentially compute the expected result
    for(int i = 1; i < size; ++i) {
        a[i] += a[i - 1];
    }

    // Verify the result of the seq clause against the expected sequential computation
    for(int i = 0; i < size; ++i) {
        if(a[i] != b[i]) {
            err++;
            break;
        }
    }

    free(a);
    free(b);
    
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