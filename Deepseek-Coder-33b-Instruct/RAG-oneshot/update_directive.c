#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i;

    // Initialize arrays
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Update array b with the values from array a
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc update device(a[0:N]) self(b[0:N])
    }

    // Verify that the update was successful
    for(i = 0; i < N; i++) {
        if(a[i] != b[i]) {
            printf("Update failed at index %d\n", i);
            return 1;
        }
    }

    printf("Update successful\n");
    return 0;
}