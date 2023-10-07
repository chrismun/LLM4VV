#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct no_create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    #pragma acc data copy(a[0:n], b[0:n]) no_create
    {
        #pragma acc kernels no_create(a)
        {
            for (int x = 0; x < n; ++x) {
                a[x] = rand() % n;
            }
        }

        #pragma acc parallel no_create(b)
        {
            int idx = omp_get_thread_num() * n / omp_get_num_threads();
            for (int x = 0; x < n / omp_get_num_threads(); ++x) {
                b[idx + x] = a[idx + x] * 2;
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (b[x] != a[x] * 2) {
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