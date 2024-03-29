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

    int a[10], b[10], c[10];
    int i;

    for (i = 0; i < 10; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    #pragma acc serial
    {
        for (i = 0; i < 10; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for (i = 0; i < 10; i++) {
        if (c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
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