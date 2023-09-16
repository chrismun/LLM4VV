#include <stdio.h>
#include <openacc.h>

#define SIZE 10240

void init(float *a, int size) {
    for (int i = 0; i < size; i++)
        a[i] = (float)(i+1);
}

void verify(float *a, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != (float)i*2) {
            fprintf(stderr, "Error at index %d: expected %f, got %f\n", i, (float)i*2, a[i]);
            return;
        }
    }
    printf("Results are correct.\n");
}

int main() {
    float *a;
    a = (float*) malloc(sizeof(float) * SIZE);
    
    init(a, SIZE);

    #pragma acc data copy(a[0:SIZE])     // Copies host data to device
    {
        #pragma acc kernels    // Compute Kernels
        {
            for (int i = 0; i < SIZE; i++) {
                a[i] *= 2;
            }
        }
        // copy back results to the host
    }

    verify(a, SIZE);

    free(a);
    return 0;
}