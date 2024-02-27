#include "acc_testsuite.h"
#ifndef T1
//T1:serial,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int * a = new int[10 * n];
    int * b = new int[10 * n];
    real_t * c = new real_t[10 * n];
    real_t * d = new real_t[10 * n];
    real_t * devc = new real_t[10 * n];
    real_t * devd = new real_t[10 * n];

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        devc[x] = c[x];
        devd[x] = d[x];
    }

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        #pragma acc data copyin(a[0:10*n], b[0:10*n]) create(c[0:10*n], d[0:10*n])
        {
            #pragma acc serial self(c[0:10*n], d[0:10*n])
            {
                #pragma acc loop
                for (int y = 0; y < 10; ++y) {
                    for (int z = 0; z < n; ++z) {
                        c[y * n + z] = a[y * n + z];
                        d[y * n + z] = b[y * n + z];
                    }
                }
            }
            #pragma acc update host(c[0:10*n], d[0:10*n])
        }
        for (int y = 0; y < 10; ++y) {
            for (int z = 0; z < n; ++z) {
                if (c[y * n + z] != a[y * n + z] || d[y * n + z] != b[y * n + z]) {
                    err += 1;
                }
            }
        }
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