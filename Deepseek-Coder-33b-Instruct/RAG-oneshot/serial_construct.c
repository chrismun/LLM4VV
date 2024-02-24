#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int *result = (int*)malloc(SIZE * sizeof(int));

    // Initialize data
    for(int i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Use OpenACC to perform operation on each element of the array
    #pragma acc parallel loop copyin(data[0:SIZE]) copyout(result[0:SIZE])
    for(int i = 0; i < SIZE; i++) {
        result[i] = data[i] * 2;
    }

    // Verify the result
    for(int i = 0; i < SIZE; i++) {
        if(result[i] != data[i] * 2) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}