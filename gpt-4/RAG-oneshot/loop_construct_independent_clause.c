#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100000

// Function to verify the result
int verify(float* a, int size) {
    float sum = 0.0;
    for(int i = 0; i < size; i++){
        sum += a[i];
    }
    if(abs(sum - size) > 0.000001){
        return 0;
    }else{
        return 1;
    }
}

int main(int argc, char *argv[]) {
    float* arr;
    float total = 0.0;
    
    // Allocate memory
    arr = (float*)_mm_malloc(SIZE * sizeof(float), 64);
    
    // Initialize array with 1's
    for(int i = 0; i < SIZE; i++){
        arr[i] = 1.0;
    }
    
    #pragma acc data copy(arr[0:SIZE])
    {
        #pragma acc parallel loop independent reduction(+:total)
        for (int i = 0; i < SIZE; i++) {
            total += arr[i];
        }
    }

    printf("Sum: %f\n", total);

    if(verify(arr, SIZE)){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }

    _mm_free(arr);

    return 0;
}