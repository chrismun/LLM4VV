#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    real_t *h_src = (real_t *)malloc(n * sizeof(real_t));
    real_t *h_dest = (real_t *)malloc(n * sizeof(real_t));
    real_t *d_src, *d_dest;

    for (int x = 0; x < n; ++x){
        h_src[x] = rand() / (real_t)(RAND_MAX / 10);
        h_dest[x] = 0.0;
    }

    d_src = acc_copyin(h_src, n * sizeof(real_t));
    d_dest = acc_copyin(h_dest, n * sizeof(real_t));

    acc_memcpy_d2d(d_dest, d_src, n * sizeof(real_t), 1, 1);
    acc_memcpy_d2d_async(d_dest, d_src, n * sizeof(real_t), 1, 1, 1);

    acc_copyout(h_dest, n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        if (fabs(h_dest[x] - h_src[x]) > PRECISION){
            err += 1;
        }
    }

    free(h_src);
    free(h_dest);

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