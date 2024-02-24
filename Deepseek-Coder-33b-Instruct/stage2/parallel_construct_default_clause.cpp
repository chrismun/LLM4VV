#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#define N 1000000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for(int i = 0; i < N; i++) {
        if(c[i] != 2*i) {
            std::cout << "Test failed\n";
            return 1;
        }
    }

    std::cout << "Test passed\n";
    return 0;
}