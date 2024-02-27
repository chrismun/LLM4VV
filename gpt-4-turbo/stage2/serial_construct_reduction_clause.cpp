#include <iostream>
#include <cstdlib> // for rand(), srand()
#include <vector>
#include <numeric> // for std::accumulate
#include <openacc.h>

#ifndef T1
// T1:serial construct reduction clause,V:2.7-3.3
int test1() {
    int err = 0;
    const int N = 1000;
    srand(42); // SEED

    std::vector<int> vec(N);
    for (int i = 0; i < N; ++i) {
        vec[i] = rand() % 100; // Filling vector with random numbers
    }

    int sum_acc = 0;
    // OpenACC operation
    #pragma acc serial copy(vec[0:N]) reduction(+:sum_acc)
    for (int i = 0; i < N; ++i) {
        sum_acc += vec[i];
    }

    // CPU operation for comparison
    int sum_cpu = std::accumulate(vec.begin(), vec.end(), 0);

    // Verifying the results
    if (sum_acc != sum_cpu) {
        std::cerr << "Mismatch: sum_acc = " << sum_acc << ", sum_cpu = " << sum_cpu << std::endl;
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    const int NUM_TEST_CALLS = 10; // Example constant
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}