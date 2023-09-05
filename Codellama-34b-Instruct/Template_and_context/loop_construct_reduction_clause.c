#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int x = 0;
    int y = 0;
    int z = 0;

    #pragma acc parallel copy(x) reduction(+:x,y)
    {
        #pragma acc loop gang vector reduction(+:x,z)
        for (int i = 0; i < I; ++i) {
            x += 1;
            z += 2;
        }
        y += z;
    }

    if (x != I || y != I * 2) {
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