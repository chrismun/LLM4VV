#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void initialize_array(float* a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

void print_array(float* a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
}

int main() {
    int n = 10;
    float* a = (float*)malloc(n * sizeof(float));
    float* b = (float*)malloc(n * sizeof(float));

    // Initialize array on host
    initialize_array(a, n);
    printf("Array on host: ");
    print_array(a, n);

    // Attach array to device
    acc_attach(&a);
    printf("Array attached on device: ");
    print_array(a, n);

    // Perform computation on device
    #pragma acc parallel loop present(a)
    for (int i = 0; i < n; i++) {
        a[i] *= 2;
    }

    // Detach array from device
    acc_detach(&a);
    printf("Array detached from device: ");
    print_array(a, n);

    free(a);
    free(b);

    return 0;
}