#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define M 100
#define TILE_DIM 10

void matrix_mul( int n, int m, float* A, float* B, float* C) {
    int i, j, k;
    for (i = 0; i < n; ++i){
        for (j = 0; j < m; ++j){
            float temp = 0.0;
            for (k = 0; k < m; ++k)
                temp += A[i*m + k] * B[k*m + j];
            C[i*m + j] = temp;
        }
    }
}

int main() {
    int n = N;
    int m = M;
    float *A, *B, *C, *checkC;
    A = (float*) malloc(n*m*sizeof(float));
    B = (float*) malloc(m*m*sizeof(float));
    C = (float*) malloc(n*m*sizeof(float));
    checkC = (float*) malloc(n*m*sizeof(float)); 

	// OpenACC test block
    #pragma acc data copyin(A[0:n*m], B[0:m*m]), copyout(C[0:n*m])
    {
        #pragma acc parallel loop tile(TILE_DIM, TILE_DIM)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                float temp = 0.0;
                for (int k = 0; k < m; ++k)
                    temp += A[i*m + k] * B[k*m + j];
                C[i*m + j] = temp;
            }
        }
    }

    // Run the same operation on CPU to check result
    matrix_mul(n, m, A, B, checkC);

    // Verify results
    float maxError = 0.0;
    for (int i = 0; i < n*m; i++)
        if (maxError < abs(C[i]-checkC[i]))
            maxError = abs(C[i]-checkC[i]);
    printf("Max error: %f\n", maxError);

    return 0;
}