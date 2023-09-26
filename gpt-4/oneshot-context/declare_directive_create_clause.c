#include <stdio.h>

#pragma acc declare create(A)

void initialize_A(int * A, int size) {
    #pragma acc parallel loop
    for(int i = 0; i < size; i++) {
        A[i] = i;
    }
}

void print_A(int * A, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int size = 10;
    int * A = new int[size];

    initialize_A(A, size);

    // Copy data back to the host
    #pragma acc update host(A[0:size])

    print_A(A, size);
    
    delete [] A;
    
    return 0;
}