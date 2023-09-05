#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() 
{
    const int N = 1000000;
    int *data = (int*) malloc(N*sizeof(int));
    int sum = 0;
    int i;
    
    // Initialize array
    for(i = 0; i < N; i++)
        data[i] = 1;

    #pragma acc parallel loop copyin(data[0:N]) reduce(+:sum)
    for(i = 0; i< N; i++){  
        #pragma acc atomic update
        sum += data[i]; 
    }

    printf("Sum: %d\n", sum);

    return 0;
}