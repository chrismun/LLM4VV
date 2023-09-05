pp
#include "acc_testsuite.h"
#ifndef T4
//T4:data,data-region,attach,reference-counting,V:2.7-2.7
int test4(){
    int err = 0;
    srand(SEED);

    size_t a_size = n * sizeof(real_t);
    real_t * a = (real_t *)malloc(a_size);
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    // Allocate and initialize data on device
    #pragma acc enter data create(a[0:n])

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    // Attach the data to the device
    #pragma acc data attach(b[0:n]) present(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    // Delete the data from the device
    #pragma acc exit data delete(a[0:n])

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
    return failcode;
}