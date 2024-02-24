#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *data = (int*)malloc(SIZE * sizeof(int));
    int i;

    // Initialize the array
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop auto
    for(i = 0; i < SIZE; i++) {
        data[i]++;
    }

    // Verify the results
    int errors = 0;
    for(i = 0; i < SIZE; i++) {
        if(data[i] != i+1) {
            errors++;
        }
    }

    if(errors == 0) {
        printf("All elements incremented correctly.\n");
    } else {
        printf("Incorrect number of elements incremented.\n");
    }

    free(data);
    return 0;
}