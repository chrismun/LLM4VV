#include "acc_testsuite.h"

/*T1:declare directive create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    
    // Allocate memory space for an integer
    int* testVector = (int*) malloc(sizeof(int) * 10);

    #pragma acc declare create(testVector[0:10])

    // Initialize the int array in a parallel region
    #pragma acc parallel loop copyout(testVector[0:10])
    for (int i = 0; i < 10; ++i) {
        testVector[i] = rand();
    }

    // Check values on the Host
    #pragma acc update host(testVector[0:10])
    for (int i = 0; i < 10; ++i) {
        if (testVector[i] == 0) {
            ++err;
        }
    }

    free(testVector);
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
     
    return failcode;
}