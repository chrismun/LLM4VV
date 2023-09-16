#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool verify(double *arr1, double *arr2, size_t size) {
    for(size_t i=0; i<size; i++) {
        if(arr1[i]!=arr2[i])
            return false;
    }
    return true;
}

int main() {
    size_t size = 1024;
    double* h_a = (double*) malloc(size*sizeof(double));
    double* h_b = (double*) malloc(size*sizeof(double));

    for(size_t i=0; i<size; i++) {
        h_a[i] = (double) rand()/ RAND_MAX;
    }

    double* d_a;
    double* d_b;
    acc_set_device_num(1, acc_device_nvidia);
    d_a = (double*)acc_malloc(size*sizeof(double));
    d_b = (double*)acc_malloc(size*sizeof(double));

    acc_memcpy_to_device(d_a, h_a, size*sizeof(double));

    acc_memcpy_device(d_b, d_a, size*sizeof(double));

    acc_memcpy_from_device(h_b, d_b, size*sizeof(double));

    if (!(verify(h_a, h_b, size))) {
        printf("Device to device memory copy failed\n");
        return 1;
    }

    free(h_a);
    free(h_b);

    acc_free(d_a);
    acc_free(d_b);

    printf("Device to device memory copy passed\n");
    return 0;
}