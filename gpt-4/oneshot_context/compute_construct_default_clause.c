#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int n = 1000;

void sum_array_default_present(float* a, float* total) {
    #pragma acc parallel loop default(present)
    for (int i = 0; i < n; i++) {
        *total += a[i];
    }
}

void sum_array_default_none(float* a, float* total) {
    #pragma acc parallel loop default(none) present(a, total)
    for (int i = 0; i < n; i++) {
        *total += a[i];
    }
}

int main() {
    float* a = (float*) malloc(n * sizeof(float));
    float total_present = 0, total_none = 0;

    // Initialize array with random numbers
    for (int i = 0; i < n; i++) {
        a[i] = (float)rand()/(float)(RAND_MAX);
    }

    // Copy array a to device manually
    #pragma acc enter data copyin(a[0:n], total_present, total_none)

    sum_array_default_present(a, &total_present);
    sum_array_default_none(a, &total_none);

    // Copy result back to host
    #pragma acc exit data copyout(total_present, total_none)

    printf("Total (default present): %f\n", total_present);
    printf("Total (default none): %f\n", total_none);

    return 0;
}