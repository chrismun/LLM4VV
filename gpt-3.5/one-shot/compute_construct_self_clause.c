#include <stdio.h>
#include <stdlib.h>

void saxpy(int n, float a, float *x, float *y)
{
    #pragma acc kernels
    {
        #pragma acc loop independent
        for (int i = 0; i < n; i++)
        {
            y[i] += a * x[i];
        }
    }
}

int main()
{
    int n = 100;
    float a = 2.0f;

    float *x = (float *)malloc(n * sizeof(float));
    float *y = (float *)malloc(n * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < n; i++)
    {
        x[i] = i;
        y[i] = 0;
    }

    // Perform SAXPY computation
    #pragma acc data copyin(x[0:n]) copyout(y[0:n])
    {
        #pragma acc compute self
        saxpy(n, a, x, y);
    }

    // Validate the computation
    for (int i = 0; i < n; i++)
    {
        float expected = a * x[i];
        if (y[i] != expected)
        {
            printf("Computation failed at index %d\n", i);
            return 1;
        }
    }

    printf("Computation successful\n");
    
    free(x);
    free(y);

    return 0;
}