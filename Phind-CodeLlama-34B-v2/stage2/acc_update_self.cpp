#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

#ifndef T1
/*T1:acc update self,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    #pragma acc parallel present(a, b)
    {
        int idx = acc_thread_id();
        b[idx] = a[idx];
    }

    #pragma acc update self(b[0:n])

    for (int x = 0; x < n; ++x) {
        if (a[x] != b[x]) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a, b)
    free(a);
    free(b);

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