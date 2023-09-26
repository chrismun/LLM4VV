#include "acc_testsuite.h"
#include <OpenACC/openacc.h>

// Change this to fit your system
#define ARRAY_SIZE 100

#ifndef T1
/*T1:acc update self,V:2.0-2.7*/
int test1(){
    int err = 0;
    int* a = (int*) malloc(ARRAY_SIZE * sizeof(int));
    int* b = (int*) malloc(ARRAY_SIZE * sizeof(int));

    srand(SEED);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = rand() % 256; // Fill the array with random numbers between 0 and 255
    }

    #pragma acc enter data copyin(a[0:ARRAY_SIZE])
    #pragma acc parallel loop copyout(b[0:ARRAY_SIZE])
    for (int i = 0; i < ARRAY_SIZE; i++) {
        b[i] = a[i];
    }

    acc_update_self(b, ARRAY_SIZE * sizeof(int));

    for(int i=0; i<ARRAY_SIZE; i++){
        if(a[i] != b[i]){
            err = 1;
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