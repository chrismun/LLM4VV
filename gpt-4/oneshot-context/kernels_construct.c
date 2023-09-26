#include <stdio.h>
#include <openacc.h>

void openacc_test() {
    int i, N = 100000;
    float a[N];
    float b[N];
    float scalar = 3.0;

    // Initialize arrays
    for (i = 0; i < N; ++i) {
        a[i] = i * 1.0;
        b[i] = 0;
    }

    // OpenACC Kernels
    #pragma acc kernels copyin(a[0:N]), copyout(b[0:N])
    {
        #pragma acc loop independent
        for (i = 0; i < N; ++i) {
            b[i] = scalar * a[i];
        }
    }
}

int main() {
    openacc_test();
    return 0;
}