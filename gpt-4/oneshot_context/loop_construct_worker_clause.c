#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1000

int main()
{
    int *data;
    data = (int*)malloc(sizeof(int) * SIZE);

    // initialize the data array on CPU
    for(int i = 0; i < SIZE; i++ )
    {
        data[i] = i;
    }

    // Use the OpenACC data construct to transfer the data array to the device
    #pragma acc data copy(data[0:SIZE])
    {
        // Use the num_workers clause to specify that the loop inside the parallel region should 
        // be divided amongst the 10 workers.
        #pragma acc parallel loop worker(10)
        for(int i = 0; i < SIZE; i++ )
        {
            data[i] = data[i] * 2;
        }
    }

    // Print few output data elements
    for(int i = 0; i < 10; i++)
    {
        printf("%d ", data[i]);
    }

    free(data);
    return 0;
}