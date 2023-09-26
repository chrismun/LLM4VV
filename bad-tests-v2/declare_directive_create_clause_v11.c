#include "acc_testsuite.h"
#ifndef T1
/*T1:declare directive create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    #pragma acc declare create(a[0:n])
    {
        #pragma acc parallel present(a[0:n])
        {
            for (int x = 0; x < n; ++x) {
                a[x] = rand() % n;
            }
        }
    }

    #pragma acc declare create(b[0:n])
    {
        #pragma acc kernels present(b[0:n])
        {
            for (int x = 0; x < n; ++x) {
                b[x] = rand() % n;
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (a[x] != b[x]) {
            err = 1;
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