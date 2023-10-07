#include "acc_testsuite.h"
#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_dev = (real_t *)acc_malloc(n * sizeof(real_t));
    real_t *b_dev = (real_t *)acc_malloc(n * sizeof(real_t));
    real_t *c_dev = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    acc_map_data(a, a_dev, n * sizeof(real_t));
    acc_map_data(b, b_dev, n * sizeof(real_t));
    acc_map_data(c, c_dev, n * sizeof(real_t));

    #pragma acc parallel present(a, b, c)
    {
        int x = acc_thread_id();
        c[x] = a[x] + b[x];
    }

    acc_unmap_data(a);
    acc_unmap_data(b);
    acc_unmap_data(c);

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    acc_free(a_dev);
    acc_free(b_dev);
    acc_free(c_dev);
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