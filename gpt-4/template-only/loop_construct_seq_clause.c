#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 10000

int test_seq_clause() {
    int i, err = 0;
    float* array = (float*) malloc(ARRAY_SIZE * sizeof(float));

    for(i = 0; i < ARRAY_SIZE; i++)
        array[i] = (float)i;
    
    float sum = 0.0;
    
    #pragma acc parallel loop seq
    for(i = 0; i < ARRAY_SIZE; i++)
        sum += array[i];
    
    // Check the result
    float expected_sum = ((float)ARRAY_SIZE-1)*(float)ARRAY_SIZE/2;  // Sum of arithmetic series
    if (sum != expected_sum)
        err = 1;

    free(array);
    return err;
}

int main(){
    int failcode = 0;

    failcode = test_seq_clause();

    if(failcode != 0){
        printf("Test failed.\n");
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}