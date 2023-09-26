#include "acc_testsuite.h"

#ifndef T1
/*T1:kernels construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Initializing necessary variables
    size_t length = 10; // Modify the length as needed
    int* a = (int*)malloc(sizeof(int) * length);
    int* b = (int*)malloc(sizeof(int) * length);

    // Populating the array with random numbers
    for (size_t i = 0; i < length; ++i) {
        a[i] = (int)rand();
    }

    // Using kernels construct private clause
    #pragma acc kernels
    {
        int private_variable = 0;

        #pragma acc loop private(private_variable)
        for (size_t i = 0; i < length; ++i) {
            private_variable = a[i];
            if (b[i] != a[i]){
                err = 1;
            }
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