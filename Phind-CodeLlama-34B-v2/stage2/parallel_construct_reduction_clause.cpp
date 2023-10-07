#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int n = 1000;
    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));
    real_t sum = 0.0;

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc parallel copy(a[0:n], b[0:n]) reduction(+:sum)
    {
        int i = acc_thread_id();
        sum += a[i] * b[i];
    }

    real_t expected_sum = 0.0;
    for (int x = 0; x < n; ++x) {
        expected_sum += a[x] * b[x];
    }

    if (fabs(sum - expected_sum) > PRECISION) {
        err = 1;
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