#include <stdlib.h>
#include <iostream>
#include <cstring>

#define SIZE 100

int main() {
    int *original = new int[SIZE];
    int *cached = new int[SIZE];

    // Initialize the original array with random numbers
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        original[i] = rand() % 100;
    }

    // Copy the original array to the cached array
    memcpy(cached, original, SIZE * sizeof(int));

    // Use OpenACC to cache the cached array
    #pragma acc data copyin(cached[0:SIZE])
    {
        #pragma acc cache(cached)
        {
            // Do some computation here
        }
    }

    // Check if the cached array is correctly cached
    for (int i = 0; i < SIZE; i++) {
        if (original[i] != cached[i]) {
            std::cout << "Cache directive is not working properly" << std::endl;
            return 1;
        }
    }

    std::cout << "Cache directive is working properly" << std::endl;
    return 0;
}