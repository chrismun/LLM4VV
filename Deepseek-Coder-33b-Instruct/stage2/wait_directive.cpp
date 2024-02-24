#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define SIZE 1000000

int main() {
    std::vector<int> a(SIZE), b(SIZE), c(SIZE);
    srand(time(NULL));

    // Initialize vectors
    for (int i = 0; i < SIZE; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Perform vector addition
    #pragma acc data copyin(a, b) copyout(c)
    {
        #pragma acc parallel loop
        for (int i = 0; i < SIZE; ++i) {
            c[i] = a[i] + b[i];
        }

        // Wait for all threads to finish
        #pragma acc wait
    }

    // Check results
    for (int i = 0; i < SIZE; ++i) {
        if (c[i] != a[i] + b[i]) {
            std::cout << "Error at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}