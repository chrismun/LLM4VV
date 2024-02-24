#include <stdlib.h>
#include <time.h>
#include <iostream>

#define SIZE 1000

int main() {
    int data[SIZE], ref[SIZE];
    int sum = 0, ref_sum = 0;

    srand(time(NULL));

    // Initialize the array with random numbers
    for(int i = 0; i < SIZE; i++) {
        data[i] = rand() % 100;
        ref[i] = data[i];
    }

    // Compute the sum of the array elements
    for(int i = 0; i < SIZE; i++) {
        ref_sum += ref[i];
    }

    // Parallelize the loop using the gang clause
    #pragma acc parallel loop gang(static:1)
    for(int i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    // Check if the sum is the same
    if(sum != ref_sum) {
        std::cout << "Test failed" << std::endl;
        return 1;
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}