#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int test_acc_update_device(int n, real_t *a, real_t *b);
int test_acc_update_self(int n, real_t *a, real_t *b);

int main(){
    int failcode = 0;
    int failed;

    // Test acc update device
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_update_device(n, a, b);
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    // Test acc update self
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_update_self(n, a, b);
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }

    return failcode;
}

int test_acc_update_device(int n, real_t *a, real_t *b){
    int err = 0;

    // Initialize data
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copy data to device
    #pragma acc data copyin(a[0:n])
    {
        // Update data on device
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Copy data back to host
    #pragma acc data copyout(b[0:n])
    {
        // Update data on host
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Check results
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int test_acc_update_self(int n, real_t *a, real_t *b){
    int err = 0;

    // Initialize data
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copy data to device
    #pragma acc data copyin(a[0:n])
    {
        // Update data on device
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Update data on host
    #pragma acc data copyout(b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    // Check results
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}