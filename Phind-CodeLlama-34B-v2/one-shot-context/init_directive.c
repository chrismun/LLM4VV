#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024

int main() {
    int i;
    double *a, *b;

    a = (double *)malloc(NUM_ELEMENTS * sizeof(double));
    b = (double *)malloc(NUM_ELEMENTS * sizeof(double));

    for (i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i * 1.0;
        b[i] = 0.0;
    }

    #pragma acc init device_type(acc_device_nvidia)
    {
        #pragma acc data copyin(a[0:NUM_ELEMENTS]) copyout(b[0:NUM_ELEMENTS])
        {
            #pragma acc kernels
            {
                #pragma acc loop
                for (i = 0; i < NUM_ELEMENTS; i++) {
                    b[i] = a[i] * 2.0;
                }
            }
        }
    }

    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (b[i] != a[i] * 2.0) {
            printf("Test failed: b[%d] = %f, expected %f\n", i, b[i], a[i] * 2.0);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}