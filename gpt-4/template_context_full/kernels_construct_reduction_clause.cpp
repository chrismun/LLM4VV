#include "acc_testsuite.h"

#ifndef T1
/*T1:kernels construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    // Set a size for the array
    int size = 1024;
    #pragma acc declare create(
        arr1[size])
    // Initialize the arr1 with random values 
    srand(SEED);
    for (int i = 0; i < size; ++i) {
        arr1[i] = rand();
    }
    // Assume minimum found is the initial value at first element
    int minSeq = arr1[0];
    // Calculate min sequentially
    for (int i = 1; i < size; ++i) {
        if (arr1[i] < minSeq)
            minSeq = arr1[i];
    }
    // Now calculate min using parallel processing with OpenACC
    int minPar = arr1[0];
    #pragma acc kernels loop reduction(min:minPar)
    for (int i = 1; i < size; ++i) {
        if (arr1[i] < minPar)
            minPar = arr1[i];
    }
    // Compare the two minimum values for a match
    if(minSeq != minPar){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}