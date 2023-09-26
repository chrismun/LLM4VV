#include <stdio.h>
#include <stdlib.h>
#define N 100000

int main()
{
    int* a = (int*) malloc(sizeof(int) * N);
    int sum = 0;
    
    // Initialize array
    for (int i = 0; i < N; i++) {
        a[i] = 1;
    }

    // Cache directive to fetch array elements into the highest level of the cache within the loop
    #pragma acc parallel loop reduction(+:sum) cache(a[0:N-1])
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }    

    printf("Sum = %d\n", sum);
    
    return 0;