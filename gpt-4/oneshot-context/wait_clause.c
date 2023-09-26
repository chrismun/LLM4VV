#include <stdio.h>
#include <openacc.h>

#define SIZE 100
#define NUM_ITER 10

void vector_add(int *a, int *b, int *c, int n){
    int i;
    #pragma acc parallel loop device_type(nvidia) wait async(1)
    for(i = 0; i < n; i++){
        c[i] = a[i] + b[i];
    }
}

int main(){
    int i, j;
    int a[SIZE], b[SIZE], c[SIZE];

    // Initialize vectors
    for(i = 0; i < SIZE; i++){
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition several times
    for(j = 0; j < NUM_ITER; j++){
        #pragma acc data copyin(a[0:SIZE],b[0:SIZE]) copyout(c[0:SIZE])
        {
            vector_add(a, b, c, SIZE);
        }
        // Wait for async operation to complete
        acc_wait(1);
    }

    // Check results
    for(i = 0 ; i < SIZE; i++){
        if(c[i] != i + i){
            printf("Error at position %d, expected %d but got %d\n", i, i+i, c[i]);
            return 1;
        }
    }
    printf("OpenACC Wait Clause Test Passed\n");
    return 0;