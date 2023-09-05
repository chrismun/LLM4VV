#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>

void print_array(float* A, int N) {
    int i;
    for (i = 0; i < N; i++) {
        printf("%f ", A[i]);
    }
    printf("\n");
}

void increment(float* A, int N) {
    #pragma acc parallel loop present(A)
    for (int i = 0; i < N; i++) {
        A[i]++;
    }
}

int main() {
    const int N = 10;
    float* A = (float*) malloc(N*sizeof(float));
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
    print_array(A, N);

    void* d_A = acc_copyin(A, N*sizeof(float));
    increment(A, N);
    acc_copyout(A, N*sizeof(float));

    print_array(A, N);
    
    
    free(A);
    return 0;
   
}