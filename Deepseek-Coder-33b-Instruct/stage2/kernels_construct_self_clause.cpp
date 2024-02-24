#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#define N 1000000

int main() {
    int *a = new int[N];
    int *b = new int[N];
    int *c = new int[N];

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc loop independent
        for(int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for(int i = 0; i < N; i++) {
        if(c[i] != 2*i) {
            std::cout << "Test failed at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Test passed" << std::endl;
    return 0;
}