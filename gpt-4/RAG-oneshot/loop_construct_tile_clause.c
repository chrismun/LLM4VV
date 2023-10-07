#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

void check(int *array) {
    for(int i = 0; i < SIZE; i++) {
        if(array[i] != i*2) {
            printf("Error at index %d with value %d\n", i, array[i]);
            exit(-1);
        }
    }
    printf("Test passed successfully!\n");
}

int main() {
    int *array = (int*) malloc(SIZE * sizeof(int));

    for(int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    #pragma acc parallel loop tile(32)
    for(int i = 0; i < SIZE; i++) {
        array[i] *= 2;
    }

    check(array);

    free(array);
    return 0;
}