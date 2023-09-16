#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,data,data-region,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
        }
        #pragma acc update self(a[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 2*b[x]) > PRECISION){
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

    #ifndef T1
    for (int x = 0; x < TEST_CALL_REPEAT; ++x){
        failed += test1();
    }
    if (failed != 0){
        printf("Test failed\n");
        return 1;
    }
    #endif
    printf("Test passed\n");
    return 0;
}