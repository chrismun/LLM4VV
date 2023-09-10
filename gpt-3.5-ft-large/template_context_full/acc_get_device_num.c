#include "acc_testsuite.h"
#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c;

    gen_real_seql(a, n);
    gen_real_seql(b, n);

    for (int x = 1; x < 10; ++x){
        c = (real_t *)malloc(n * sizeof(real_t));
        acc_set_device_num(x, acc_get_device_type());
        #pragma acc enter data copyin(a[0:n], b[0:n])
        #pragma acc parallel present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int yy = 0; yy < n; ++yy){
                c[yy] = a[yy] + b[yy];
            }
        }
        #pragma acc exit data delete(a[0:n], b[0:n])
        for (int yy = 0; yy < n; ++yy){
            if (fabs(c[yy] - (a[yy] + b[yy])) > PRECISION){
                err += 1;
            }
        }
        delete[]c;
    }
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