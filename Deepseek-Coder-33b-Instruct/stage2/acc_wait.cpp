#include <iostream>
#include <openacc.h>

int main() {
    int n = 1000000;
    int *a = new int[n];
    int *b = new int[n];

    // Initialize arrays
    for(int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition
    #pragma acc parallel loop copyin(a[0:n], b[0:n]) copyout(a[0:n])
    for(int i = 0; i < n; i++) {
        a[i] += b[i];
    }

    // Wait for all devices to finish
    acc_wait_all();

    // Check the results
    for(int i = 0; i < n; i++) {
        if(a[i] != 2*i) {
            std::cout << "Error at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "All tests passed" << std::endl;
    return 0;
}