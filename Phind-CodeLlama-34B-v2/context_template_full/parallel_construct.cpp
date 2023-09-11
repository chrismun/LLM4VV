#include <iostream>
#include <cstdlib>
#include <cmath>
#include "acc_testsuite.h"

using namespace std;

#ifndef T1
/*T1:parallel construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 1000;
    int *a = new int[array_size];
    int *b = new int[array_size];

    for (int i = 0; i < array_size; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc parallel copy(a[0:array_size], b[0:array_size])
    {
        #pragma acc loop
        for (int i = 0; i < array_size; i++) {
            b[i] = a[i] + 1;
        }
    }

    for (int i = 0; i < array_size; i++) {
        if (b[i] != a[i] + 1) {
            err = 1;
            break;
        }
    }

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