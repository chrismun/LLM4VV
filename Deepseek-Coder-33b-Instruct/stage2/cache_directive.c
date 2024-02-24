#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 1000

int main() {
    int data[SIZE];
    int i;
    srand(time(NULL));

    // Initialize the array with random numbers
    for (i = 0; i < SIZE; i++) {
        data[i] = rand() % 100;
    }

    // Use the cache directive to cache the array in the device memory
    #pragma acc parallel loop copy(data[0:SIZE])
    for (i = 0; i < SIZE; i++) {
        #pragma acc cache(data[i])
        {
            data[i] = data[i] * 2;
        }
    }

    // Print the array
    for (i = 0; i < SIZE; i++) {
        printf("%d ", data[i]);
    }

    return 0;
}