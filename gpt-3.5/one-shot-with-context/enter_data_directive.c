#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

void initialize_array(float* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
}

int verify_sum(float* array, int size) {
    float sum = (size - 1) * (size / 2.0);
    for (int i = 0; i < size; i++) {
        sum -= array[i];
    }
    if (sum == 0) return 1;
    return 0;
}

int main() {
    float* array = (float*)malloc(N * sizeof(float));

    initialize_array(array, N);

    #pragma acc enter data create(array[0:N])

    // Perform some operations on the array using OpenACC directives

    #pragma acc parallel loop
    for (int i = 0; i < N; i++) {
        array[i]++;
    }

    #pragma acc exit data copyout(array[0:N])

    // Verify the correctness of the result
    int success = verify_sum(array, N);
    printf("Success: %d\n", success);

    free(array);

    return 0;