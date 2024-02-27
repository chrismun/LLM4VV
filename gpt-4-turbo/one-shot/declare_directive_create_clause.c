#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 100000
#define SEED 12345
#define PRECISION 0.00001

// Declare a helper function to generate some computation - e.g., a simple operation
void generate_data(real_t *data, int count) {
    for (int i = 0; i < count; ++i) {
        data[i] = i * 10.0;
    }
}

int main() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));  // This will be used to validate the result

    generate_data(a, n);  // Generate initial data

    // Declare `b` on the device without initializing it. We'll generate its values on the device.
    #pragma acc data create(b[0:n])
    {
        // Generate b values similarly to `a` but on device
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x) {
            b[x] = x * 10.0;
        }
    }

    // After running on the device, b is not directly updated on the host, as it is 'create'-d. 
    // If you wish to compare, you need to copy it back manually, demonstrating understanding of the 'create' clause.
    #pragma acc update host(b[0:n])

    // Validate the results
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

    if (err) {
        printf("Test failed with %d errors.\n", err);
        return 1;
    } else {
        printf("Test passed.\n");
        return 0;
    }
}