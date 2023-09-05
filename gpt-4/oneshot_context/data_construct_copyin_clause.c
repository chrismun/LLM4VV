#include <stdio.h>
#include <openacc.h>

#define SIZE 100

int main()
{
    int a[SIZE];
    int b[SIZE];

    // Initialize the array 'a'
    for (int i=0; i<SIZE; i++) {
        a[i] = i * 2;
    }

    // Copy 'a' to the device using 'copyin' clause
    #pragma acc data copyin(a)
    {
        // Process the data on the GPU
        # pragma acc kernels
        for (int i=0; i<SIZE; i++) {
            b[i] = a[i];
        }
    }
    // Check the result
    for (int i=0; i<SIZE; i++) {
        // if b[i] is not same as a[i], print error and return -1
        if (b[i] != a[i]) { 
            printf("Error: Copyin failed at index %d, b[%d] = %d, expected = %d\n", i, i, b[i], a[i]);
            return -1;
        }
    }

    printf("OpenACC copyin operation successful!\n");
    return 0;