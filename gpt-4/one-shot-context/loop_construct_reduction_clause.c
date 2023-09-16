#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <openacc.h>

// Set the array size
#define N 1000000

int main() {
    // Allocate array memory 
    int* a = (int*) malloc(N * sizeof(int));
    assert(a != NULL);

    // Initialize array
    for (int i = 0; i < N; i++) {
        a[i] = 1;
    }

    // Sequential sum
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }
  
    printf("Sequential sum: %d\n", sum); 

    // OpenACC reduction
    int acc_sum = 0;
    #pragma acc parallel loop copyin(a[0:N]) reduction(+:acc_sum)
    for (int i = 0; i < N; i++) {
        acc_sum += a[i];
    }

    printf("Parallel sum with OpenACC reduction: %d\n", acc_sum);

    // Free memory
    free(a);

    // Check the results
    assert(sum == acc_sum);

    return 0;
}