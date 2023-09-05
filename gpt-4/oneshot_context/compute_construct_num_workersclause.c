#include <stdio.h>
#include <openacc.h>

int main()
{
    const int N = 1000000;
    const int num_workers = 4;
    float a[N];

    // Initialize values
    for(int i = 0; i < N; ++i)
    {
        a[i] = 1.0f * i;
    }

    #pragma acc parallel loop num_workers(num_workers) copy(a)
    for (int i = 0; i < N; ++i)
    {
        a[i] = a[i] * 2.0f;
    }

    // Validation
    for (int i = 0; i < N; ++i)
    {
        if (a[i] != i * 2.0f)
        {
            printf("Validation failed at index %d\n", i);
            return -1;
        }
    }

    printf("Validation passed.\n");
    return 0;
}