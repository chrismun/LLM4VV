#include "acc_testsuite.h"
#ifndef T5
//T5:present,if_present,V:1.0-2.7
int test5(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data present(a[0:n], b[0:n])
    {
        // Perform some computation on the accelerator
        #pragma acc parallel num_gangs(1) if_present(a)
        {
            #pragma acc loop gang worker independent
            for (int x = 0; x < n; ++x){
                a[x] += 1;
            }
        }

        // Transfer data back to the host
        #pragma acc host_data if_present(a)
        {
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Check if the data was correctly transferred back to the host
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}