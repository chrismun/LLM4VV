#include <stdio.h>

#define SIZE 100

int main() {
    int a[SIZE], b[SIZE], c[SIZE];

    for (int i = 0; i < SIZE; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc parallel loop vector(4) present(a[SIZE], b[SIZE], c[SIZE])
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    for (int i = 0; i < SIZE; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("c[%d] = %d, expected %d\n", i, c[i], a[i] + b[i]);
            return 1;
        }
    }
  
    printf("Test passed\n");
    return 0;