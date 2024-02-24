#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i, err = 0;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[:N]) copyout(b[:N])
    {
        #pragma acc update device(a[:N])
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    if (err) {
        std::cout << "Test failed with " << err << " errors." << std::endl;
        return 1;
    } else {
        std::cout << "Test passed." << std::endl;
        return 0;
    }
}