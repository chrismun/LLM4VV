#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main()
{
    int n = 1000;
    float *numbers = malloc(n * sizeof(float));
    float result = 0.0;

    for(int i = 0; i < n; i++)
    {
        numbers[i] = rand() % 10;           
    }

    // OpenACC Parallel region which performs the reduction  
    #pragma acc parallel loop reduction(+:result)
    for(int i = 0; i < n; i++)
    {
        result += numbers[i];
    }

    printf("Sum: %f\n", result);
    free(numbers);

    return 0;
}