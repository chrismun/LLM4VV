#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = rand() % 100;
    int b = rand() % 100;
    int result = 0;

    #pragma acc serial
    {
        result = a + b;
    }

    if (result != a + b){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    #endif

    return failcode;
}