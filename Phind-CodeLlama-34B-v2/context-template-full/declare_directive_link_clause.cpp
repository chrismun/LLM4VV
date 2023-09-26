#include "acc_testsuite.h"
#ifndef T1
/*T1:declare directive link clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    #pragma acc declare link(a, b, c)

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            for (int x = 0; x < n; ++x) {
                a[x] = b[x] + c[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (a[x] != b[x] + c[x]) {
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);

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