#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024
#define SEED 42
#define PRECISION 0.0001

int main() {
    int err = 0;
    float *a, *b;
    acc_device_t dev_type = acc_get_device_type();
    int dev_num = acc_get_device_num(dev_type);

    a = (float*)malloc(N * sizeof(float));
    b = (float*)malloc(N * sizeof(float));

    // Initialize arrays
    srand(SEED);
    for (int i = 0; i < N; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = 0.0f;
    }

    // Computation on the device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i] * 2.0f;
            }
        }
    }

    // Check results and report any errors
    for (int i = 0; i < N; i++) {
        if (abs(b[i] - (a[i] * 2.0f)) > PRECISION) {
            err++;
        }
    }

    if (err == 0) {
        printf("PASSED: All computed values are correct.\n");
    } else {
        printf("FAILED: There are %d incorrect values.\n", err);
    }

    // Shutdown the device used
    acc_shutdown_device(dev_num, dev_type);
    // Alternatively, to shutdown all devices of specific type
    //acc_shutdown(dev_type);
    
    free(a);
    free(b);

    return err;
}