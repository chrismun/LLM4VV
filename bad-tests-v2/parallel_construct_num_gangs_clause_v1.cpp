#include "acc_testsuite.h"
#include <cmath>

#ifndef T1
/*T1:parallel construct num_gangs clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    const int N = 1000;
    int *a = new int[N];
    
    for (int i = 0; i < N; ++i) {
        a[i] = i;
    }

    #pragma acc parallel num_gangs(50) copy(a[0:N])
    {
        #pragma acc loop gang
        for (int i = 0; i < N; i++) {
            a[i] = sqrt(a[i]);
        }
    }

    for (int i = 0; i < N; ++i) {
        if (a[i] != sqrt(i)) {
            err = 1;
        }
    }
    delete[] a;
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