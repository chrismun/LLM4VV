#include <stdio.h>
#include <stdlib.h>

int main() {
    /* Size of array */
    int N = 100;

    /* Host memory */
    float *h_a;
    float *h_b;

    /* Allocate host memory */
    h_a = (float*)malloc(N*sizeof(float));
    h_b = (float*)malloc(N*sizeof(float));

    /* Initialize host arrays */
    for(int i=0; i<N; i++) {
        h_a[i] = 1.0f;
        h_b[i] = 0.0f;
    }

    /* Compute on device */
    #pragma acc data copyin(h_a[0:N]), copy(h_b[0:N])
    {
        /* Compute vector Add */
        #pragma acc kernels
        for(int i=0; i<N; i++) {
            h_b[i] = h_a[i];
        }
    }

    /* Check for errors */
    for(int i=0; i<N; i++) {
        if(h_b[i] != h_a[i]) {
            printf("Error at position %d! Expected %f but got %f\n", i, h_a[i], h_b[i]);
            return -1;
        }
    }

    printf("Correct result!\n");

    /* Clean up memory */
    free(h_a);
    free(h_b);

    return 0;
}