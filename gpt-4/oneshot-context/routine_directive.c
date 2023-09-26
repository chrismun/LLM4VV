#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#pragma acc routine seq  // Using routine directive
float square(float num)  // Defining a function to return the square of a number
{
  return num * num;
}

int main()
{
    int n = 10;
    float* a = (float*) malloc(n * sizeof(float));

    // Initialize array
    for(int i = 0; i < n; i++)
    {
        a[i] = i;
    }

    // Calculate square of each number using OpenACC
    #pragma acc parallel loop copy(a[0:n])
    for(int i = 0; i < n; i++)
    {
        a[i] = square(a[i]); // Call to accelerator routine
    }

    // Print array
    for(int i = 0; i < n; i++)
    {
        printf("Square of %d: %.2f\n", i, a[i]);
    }

    free(a);

    return 0;
}