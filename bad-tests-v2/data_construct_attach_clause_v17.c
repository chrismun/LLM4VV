#include "acc_testsuite.h"

#ifndef T1
//T1:kernels,data,data-region,V:2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * x = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        x[i] = rand() / (real_t)(RAND_MAX / 10);
    }

    real_t *d_x;
    #pragma acc enter data copyin(x[0:n])
    {
        d_x = acc_deviceptr(x);
    }

    real_t * y = (real_t *)malloc(n * sizeof(real_t));
    #pragma acc enter data attach(y[0:n] : d_x[0:n])

    #pragma acc parallel present(x[0:n],y[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            y[i] = x[i];  // Test to check whether data from "x" is successfully copied to "y"
        }
    }

    // Validate
    for (int i = 0; i < n; ++i){
        if (fabs(y[i] - x[i]) > PRECISION){
            err++ ; 
        }
    }

    // Clean up
    #pragma acc exit data delete(x[0:n], y[0:n])

    return err;
}
#endif

int main(){
    // Initiate test
    int fail = 0;
    int error;
#ifndef T1
    error = 0;
    for (int i = 0; i < NUM_TEST_ITERATIONS; ++i){
        error += test1();
    }
    if (error != 0){ 
        //error present
        fail += (1 << 0);
    }
#endif

    return fail;
}