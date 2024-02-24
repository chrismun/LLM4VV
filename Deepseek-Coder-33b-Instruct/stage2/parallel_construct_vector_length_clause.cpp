#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <openacc.h>

#define N 1000000
#define VECTOR_LENGTH 256

int main() {
    srand(time(NULL));

    int *a = new int[N];
    int *b = new int[N];

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform vector addition in parallel
    #pragma acc parallel loop vector_length(VECTOR_LENGTH)
    for (int i = 0; i < N; i++) {
        a[i] += b[i];
    }

    // Check the results
    for (int i = 0; i < N; i++) {
        if (a[i] != (rand() % 100) + (rand() % 100)) {
            std::cout << "Test failed at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}