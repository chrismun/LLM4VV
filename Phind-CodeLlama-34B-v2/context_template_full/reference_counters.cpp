#include "acc_testsuite.h"
#ifndef T1
/*T1:reference counters,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data copyin(b[0:n])

    #pragma acc parallel present(a[0:n], b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            a[x] = b[x] + 1;
        }
    }

    #pragma acc exit data copyout(a[0:n])
    #pragma acc exit data delete(b[0:n])

    for (int x = 0; x < n; ++x) {
        if (a[x] != b[x] + 1) {
            err = 1;
            break;
        }
    }

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