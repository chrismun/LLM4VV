#include <stdio.h>
#include <openacc.h>

int main() {
    int n = 1000000;
    int a[n], b[n];

    // Initialize arrays
    for(int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Create a parallel region
    #pragma acc parallel loop
    for(int i = 0; i < n; i++) {
        // Detach a task
        #pragma acc detach
        {
            // Perform some computation
            b[i] = a[i] * 2;
        }
    }

    // Wait for all tasks to complete
    #pragma acc wait

    // Check the results
    for(int i = 0; i < n; i++) {
        if(b[i] != a[i] * 2) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}