#include <stdio.h>
#include <openacc.h>

#define N 1000000

int main() {
    int i, a[N], b[N], c[N];
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels async
        {
            for (i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
            }
        }

        // Wait for all asynchronous operations to complete
        acc_async_wait(1);

        // Check if the async operations have completed
        for (i = 0; i < N; i++) {
            if (c[i] != a[i] + b[i]) {
                printf("Error: Async operation not completed correctly\n");
                return 1;
            }
        }
    }

    printf("Async test passed\n");
    return 0;
}