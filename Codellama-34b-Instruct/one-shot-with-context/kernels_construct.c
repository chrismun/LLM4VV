#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345
#define PRECISION 1e-6

int test1(int n, int num_gangs, int num_workers, int vector_length, int device_type, int if_condition, int self_condition, int copy_condition, int copyin_condition, int copyout_condition, int create_condition, int no_create_condition, int present_condition, int deviceptr_condition, int attach_condition) {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc kernels async(num_gangs, num_workers, vector_length) device_type(device_type) if(if_condition) self(self_condition) copy(copy_condition) copyin(copyin_condition) copyout(copyout_condition) create(create_condition) no_create(no_create_condition) present(present_condition) deviceptr(deviceptr_condition) attach(attach_condition)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            b[x] = a[x];
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1(10, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}