#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

int main() {
    int n = 10000;
    float* A = (float*)malloc(n*sizeof(float));
    float* B = (float*)malloc(n*sizeof(float));
    for (int i = 0; i < n; i++) {
        A[i] = (float)i;
        B[i] = 0.0;
    }

    #pragma acc data copyin(A[0:n]) copyout(B[0:n])
    {
        #pragma acc parallel loop independent
        for (int i = 0; i < n; i++) {
            B[i] = A[i] * 2.0;
        }
    }
    
    // Validate results
    for (int i = 0; i < n; i++) {
        if (B[i] != A[i] * 2.0) {
            printf("Result mismatch at index %d! B[i]: %f, Expected : %f \n", i, B[i], A[i]*2.0);
            exit(1);
        }
    }

    printf("Pass\n");
    free(A);
    free(B);
    return 0;