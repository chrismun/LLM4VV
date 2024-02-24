#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, a[N], b[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // OpenACC region
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc parallel loop default(present)
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Verify results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification successful\n");
    return 0;
}