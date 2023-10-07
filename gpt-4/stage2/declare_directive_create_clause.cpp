#include "acc_testsuite.h"
#ifndef T1
/*Test for OpenACC declare directive create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable
    int *p;
    const int size = 10;

    // Allocate memory using create clause
    #pragma acc declare create(p[0:size])

    p=(int*)malloc(size*sizeof(int));
    // Fill the variable
    for(int i = 0; i < size; ++i)
    {
        p[i] = rand();
    }

    // Perform operation on the variable
    #pragma acc parallel loop
    for(int i = 0; i < size; ++i)
    {
        p[i] *= 2;
    }

    // Check results
    for(int i = 0; i < size; ++i)
    {
        if(p[i] % 2 != 0){
            err = 1;
        }
    }
    free(p);
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