#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,declare,V:2.5-2.7
int test1(){
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    srand(SEED);

    for(int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc declare create(b[0:n])
    {
        #pragma acc parallel copyin(a[0:n]) copy(b[0:n])
        {
            #pragma acc loop
            for(int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }
    for(int x = 0; x < n; ++x) {
        if(fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failed = 0;
    int test_result = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        test_result = test1();
        failed += test_result;
    }

    if (failed != 0) {
        printf ("Test failed\n");
        return 1;
    }
#endif
    printf ("Test passed\n");
    return 0;
}