#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10000

int main(){
    int *a;
    int sum = 0, check_sum = 0;
    int failcode = 0;

    a = (int*)malloc(SIZE * sizeof(int));

    // Fill the array with random numbers
    for(int i=0; i<SIZE; i++){
        a[i] = rand() % 100;
        check_sum += a[i];
    }

    // Compute the sum in parallel and create an error flag if results don't match
    #pragma acc parallel loop reduction(+:sum) 
    for(int i=0; i<SIZE; i++){
        sum += a[i];
    }

    // Checking if the parallel and serial computations match
    if(check_sum != sum){
        printf("Test Failed: sum=%d, expected_sum=%d\n", sum, check_sum);
        failcode = 1;
    }else{
        printf("Test Passed: sum=%d, expected_sum=%d\n", sum, check_sum);
    }

    free(a);

    return failcode;
}