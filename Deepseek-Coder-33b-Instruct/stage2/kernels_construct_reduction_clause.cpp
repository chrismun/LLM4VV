#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], sum = 0;

    // Initialize arrays
    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform reduction operation
    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(sum)
    {
        sum = 0;
        #pragma acc loop reduction(+:sum)
        for(int i = 0; i < N; i++) {
            sum += a[i] + b[i];
        }
    }

    // Check the result
    int expected_sum = 0;
    for(int i = 0; i < N; i++) {
        expected_sum += 2*i;
    }

    if(sum != expected_sum) {
        std::cout << "Test failed: sum is " << sum << ", expected " << expected_sum << std::endl;
        return 1;
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}