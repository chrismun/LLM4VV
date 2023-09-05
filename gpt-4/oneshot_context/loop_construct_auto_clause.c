#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main()
{
    int n = 100;
    int *arr = (int*) malloc(n*sizeof(int));
    int errors = 0;
    
    #pragma acc parallel loop auto
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    #pragma acc parallel loop auto reduction(+:errors)
    for (int i = 0; i < n; i++) {
        if (arr[i] != i) {
            errors++;
        }
    }

    if (errors==0) {
        printf("Test passed\n");
    }
    else {
        printf("Test failed with %d errors\n", errors);
    }

    free(arr);
    return 0;
}