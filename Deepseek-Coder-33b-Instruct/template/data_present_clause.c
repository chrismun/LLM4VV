#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data from 'a' to 'b' using OpenACC
    #pragma acc data copyin(a) copyout(b)
    {
        #pragma acc parallel loop present(a, b)
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Verify the data
    for (i = 0; i < N; i++) {
        if (b[i] != i) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], i);
            return 1;
        }
    }

    printf("Data copied successfully\n");
    return 0;
}