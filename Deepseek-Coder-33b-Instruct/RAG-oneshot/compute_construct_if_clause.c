#include <stdio.h>
#include <openacc.h>

int main() {
    int i;
    int a[100];
    int b[100];

    // Initialize arrays
    for (i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Parallel region
    #pragma acc parallel loop
    for (i = 0; i < 100; i++) {
        // If clause
        #pragma acc if(i < 50)
        {
            b[i] = a[i];
        }
    }

    // Verify results
    for (i = 0; i < 100; i++) {
        if (i < 50 && b[i] != a[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
        else if (i >= 50 && b[i] != 0) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Verification successful\n");
    return 0;
}