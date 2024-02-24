#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize the data
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Use OpenACC to iterate over the data sequentially
    #pragma acc parallel loop seq
    for(i = 0; i < SIZE; i++) {
        printf("data[%d] = %d\n", i, data[i]);
    }

    free(data);
    return 0;
}