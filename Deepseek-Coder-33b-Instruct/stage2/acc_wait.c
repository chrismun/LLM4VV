#include <stdio.h>
#include <openacc.h>

int main() {
    int N = 1000000;
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition
    #pragma acc parallel loop copyin(a[0:N], b[0:N]) copyout(c[0:N])
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for all asynchronous operations to complete
    acc_wait(1);

    // Check the results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}