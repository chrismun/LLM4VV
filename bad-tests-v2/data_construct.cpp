#include <iostream>
#include <cstdlib>
#include <ctime>
#include "acc_testsuite.h"

using namespace std;

#ifndef T1
/*T1:data construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 100;
    int a[N], b[N];

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }
    }

    for (int i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
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