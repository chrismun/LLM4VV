#include "acc_testsuite.h"
#ifndef T1
//T1:acc hostptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t* a = new real_t[n];
    real_t* b = new real_t[n];
    real_t* c = new real_t[n];

    for (int x  = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }
	
    for (int x  = 0; x < 7; ++x){
        acc_copyin(a, n * sizeof(real_t));
        acc_copyin(b, n * sizeof(real_t));
        acc_copyout(c, n * sizeof(real_t));
        #pragma acc hostptr(a)
        {
            #pragma acc parallel loop gang
            for (int y = 0; y < n; ++y){
                a[y] = a[y] * a[y];
            }
        }
        #pragma acc hostptr(b)
        {
            #pragma acc parallel loop gang
            for (int y = 0; y < n; ++y){
                b[y] = b[y] * b[y];
            }
        }
        #pragma acc kernel
        {
            #pragma acc loop gang
            for (int y = 0; y < n; ++y){
                c[y] = a[y] + b[y];
            }
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * a[x] + b[x] * b[x])) > PRECISION){
            err = 1;
        }
    }

    delete[] a;
    delete[] b;
    delete[] c;

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