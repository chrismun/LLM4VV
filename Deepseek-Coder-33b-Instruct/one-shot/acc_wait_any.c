#include <stdio.h>
#include <openacc.h>

int main() {
    int a[100], b[100];
    int i;

    // Initialize arrays
    for(i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Parallel region
    #pragma acc parallel loop
    for(i = 0; i < 100; i++) {
        // Task 1
        #pragma acc wait
        {
            a[i] = a[i] * 2;
        }

        // Task 2
        #pragma acc wait(any)
        {
            b[i] = a[i] * 3;
        }
    }

    // Check results
    for(i = 0; i < 100; i++) {
        if(b[i] != a[i] * 3) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}