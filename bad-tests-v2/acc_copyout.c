#include <openacc.h>
#include <stdlib.h>

int main() {

    int N = 100;
    /* Host Memory Allocation */
    float * h_a = malloc(N*sizeof(float));
    float * h_b = malloc(N*sizeof(float));

    /* Initialize host memory */
    for(int i=0; i<N; i++) {
        h_a[i] = i;
    }

    /* Device Memory Allocation and Copyin */
    #pragma acc data create(h_b[0:N])
    {
        /* Copy data from Host to Device */
        #pragma acc enter data copyin(h_a[0:N])

        /* Parallel computation on the GPU */
        #pragma acc kernels
        {
            for(int i=0; i<N; i++) {
                h_b[i] = h_a[i];
            }
        }
    }
    
    acc_copyout(h_b, N*sizeof(float));
    acc_delete(h_a, N*sizeof(float));

    /* Verify the results */
    for(int i=0; i<N; i++) {
        if(h_b[i] != h_a[i]) {
            printf("Test failed at index %d! Host: %f, Device: %f\n",
                   i, h_a[i], h_b[i]);
            return -1;
        }
    }  

    printf("Copyout and delete test passed!\n");
    
    /* Free host memory */
    free(h_a);
    free(h_b);

    return 0;
}