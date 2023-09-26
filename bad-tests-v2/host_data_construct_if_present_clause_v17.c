#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 0.0001

int validate_host_data_if_present(void);

int main() {
    int err = 0;

    err = validate_host_data_if_present();

    if (err != 0) {
        printf("Validation failed with %d errors\n", err);
    } else {
        printf("Validation passed\n");
    }

    return err;
}

int validate_host_data_if_present() {
    int i, err = 0;
    double *a, *b;

    a = (double *)malloc(NUM_ELEMENTS * sizeof(double));
    b = (double *)malloc(NUM_ELEMENTS * sizeof(double));

    for (i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i * 1.0;
        b[i] = 0.0;
    }

    #pragma acc enter data copyin(a[0:NUM_ELEMENTS])

    #pragma acc host_data use_device(a, b) if_present
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (i = 0; i < NUM_ELEMENTS; i++) {
                b[i] = a[i];
            }
        }
    }

    #pragma acc exit data copyout(b[0:NUM_ELEMENTS])

    for (i = 0; i < NUM_ELEMENTS; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}