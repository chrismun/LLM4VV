#include <iostream>
#include <cstdlib>
#include <cassert>
#include "openacc.h"

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
/*T1:acc wait,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    int *a = new int[N];
    int *b = new int[N];

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:N]) create(b[0:N])
    #pragma acc parallel present(a, b)
    {
        #pragma acc loop
        for (int i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }
    }
    #pragma acc update self(b[0:N]) async(1)
    #pragma acc wait(1)

    for (int i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a, b)
    delete[] a;
    delete[] b;

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