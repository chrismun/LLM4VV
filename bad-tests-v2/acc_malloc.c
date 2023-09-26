#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main(){
    int i;
    double *a, *b;

    /* Allocate memory on the host */
    a = (double *) malloc(N * sizeof(double));
    b = (double *) malloc(N * sizeof(double));

    /* Initialize the arrays */
    for(i = 0; i < N; i++){
        a[i] = i * 1.0;
        b[i] = 0.0;
    }

    /* Allocate memory on the device */
    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    /* Copy data to the device */
    #pragma acc update device(a[0:N])

    /* Launch kernel to perform vector addition */
    #pragma acc kernels present(a[0:N], b[0:N])
    {
        #pragma acc loop
        for(i = 0; i < N; i++){
            b[i] = a[i] * 2.0;
        }
    }

    /* Copy result back to the host */
    #pragma acc update host(b[0:N])

    /* Verify the result */
    for(i = 0; i < N; i++){
        if(fabs(b[i] - (i * 1.0 * 2.0)) > 1e-6){
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}