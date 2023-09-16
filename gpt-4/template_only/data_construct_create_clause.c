#include <stdio.h>
#include <openacc.h>

#define SIZE 1000

// The kernel function
void vecAdd(float* a, float* b, float* c) {
    #pragma acc kernels copyin(a[0:SIZE],b[0:SIZE]) copyout(c[0:SIZE])
    {
        #pragma acc loop vector
        for (int i = 0; i < SIZE; ++i) {
            c[i] = a[i] + b[i];
        }
    }
}

// Checker function
int check(float* c, float* res) {
    int i = 0, flag = 0;
    for (i = 0; i < SIZE; i++) {
        if (c[i] != res[i]) {
            flag = 1;
            printf ("index: %d, c: %f, res: %f\n", i, c[i], res[i]);
            break;
        }
    }
    return flag;
}

int main() {
    float a[SIZE];
    float b[SIZE];
    float c[SIZE];
    float res[SIZE];
    
    // Initialize arrays
    for (int i = 0; i < SIZE; ++i) {
        a[i] = i;
        b[i] = i;
        res[i] = a[i] + b[i];  // Pre-compute the expected result
    }

    // Compute on device
    vecAdd(a, b, c);

    // Check results
    int err = check(c, res);
    
    if(err == 0) {
        printf("Test passed successfully.\n");
    } else {
        printf("Test failed.\n");
    }

    return err;
}