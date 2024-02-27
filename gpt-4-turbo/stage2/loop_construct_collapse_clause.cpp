#include <iostream>
#include <cmath>
#include <cstdlib>

constexpr int SEED = 42;
constexpr int NUM_TEST_CALLS = 10;
constexpr int N = 100; // Dimensions for the matrix

#ifndef T1
// T1: loop construct collapse clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    float matrix[N][N];
    float scalar = 2.0;

    // Initialize matrix
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 100; // Simplified initialization
        }
    }

    // Apply scalar multiplication using OpenACC with collapse
#pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] *= scalar;
        }
    }

    // Verify the results
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            float expectedValue = (rand() % 100) * scalar;
            if (fabs(matrix[i][j] - expectedValue) > 0.01) {
                std::cerr << "Mismatch at (" << i << ", " << j << "): got " << matrix[i][j]
                          << ", expected " << expectedValue << std::endl;
                err++;
            }
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    srand(SEED); // Reset seed before each test run for consistency
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}