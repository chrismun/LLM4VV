#include "acc_testsuite.h"
#define SIZE 100
#define SEED 12345

#ifndef T1
/*T1:kernels construct reduction clause,V:2.0-2.7*/
int test1(){
    int i, err = 0;
    int reduction_result = 0;
    int a[SIZE];
    
    srand(SEED);

    // Initialize array with random numbers
    for(i=0; i<SIZE; i++)
        a[i] = rand()%100;

    // OpenACC kernels construct with reduction clause
    #pragma acc kernels copy(a[0:SIZE]) reduction(+:reduction_result)
    for(i=0; i<SIZE; i++)
        reduction_result += a[i];
        

    // Verification
    int expected_result = 0;
    for(i=0; i<SIZE; i++)
        expected_result += a[i];

    if(reduction_result != expected_result){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    int NUM_TEST_CALLS = 10;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}