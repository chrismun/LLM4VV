#include "acc_testsuite.h"
#ifndef T1
//T1:loop_construct_collapse, V:2.7-3.3
#define ARRAY_SIZE 16
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[10 * ARRAY_SIZE];
    real_t *b = new real_t[10 * ARRAY_SIZE];
    real_t *c = new real_t[10 * 16];
    real_t *d = new real_t[10 * 16];

    for (int x = 0; x < 10 * 16; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:10*16], b[0:10*16]) copyout(c[0:10*16]) copy(collapse, 5)
    {
        #pragma acc parallel loop collapse(2)
        for (int x = 0; x < 5; ++x){
            for (int y = 0; y < 2; ++y){
                c[x * 2 + y] = a[x * 2 + y] + b[x * 2 + y];
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 16; ++y){
            if (fabs(c[x * 16 + y] - (a[x * 16 + y] + b[x * 16 + y])) > PRECISION){
                err += 1;
            }
        }
    }

    #pragma acc data copyin(a[0:10*16], b[0:10*16]) copyout(d[0:10*16]) copy(collapse, 5)
    {
        #pragma acc parallel loop collapse(2)
        for (int x = 0; x < 5; ++x){
            for (int y = 0; y < 2; ++y){
                d[x * 2 + y] = a[x * 2 + y] + b[x * 2 + y];
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 16; ++y){
            if (fabs(d[x * 16 + y] - (a[x * 16 + y] + b[x * 16 + y])) > PRECISION){
                err += 1;
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