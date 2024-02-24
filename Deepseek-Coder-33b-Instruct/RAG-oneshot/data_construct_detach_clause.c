#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *a = (int*)malloc(SIZE * sizeof(int));
    int *b = (int*)malloc(SIZE * sizeof(int));

    // Initialize array a
    for(int i = 0; i < SIZE; i++) {
        a[i] = i;
    }

    // Copy array a to array b
    #pragma acc data copyin(a[0:SIZE]) copyout(b[0:SIZE])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(int i = 0; i < SIZE; i++) {
                b[i] = a[i];
            }
        }

        // Detach array b
        #pragma acc exit data detach(b[0:SIZE])
    }

    // Verify that array b is detached
    if(acc_is_present(b, SIZE * sizeof(int))) {
        printf("Array b is detached\n");
    } else {
        printf("Array b is not detached\n");
    }

    free(a);
    free(b);

    return 0;
}