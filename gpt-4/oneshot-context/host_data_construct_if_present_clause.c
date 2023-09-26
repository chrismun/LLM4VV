#include <stdlib.h>
#include <openacc.h>
#include <stdio.h>

#define SIZE 1024

int main()
{
    int err = 0;
    float *h_data = (float*) malloc(SIZE * sizeof(float));
    float *d_data;

    /* Initialize host data */
    for (int i = 0; i < SIZE; ++i) h_data[i] = i;

    /* Allocate device data */
    d_data = (float *)acc_malloc(SIZE * sizeof(float));

    /* Copy host data to device data */
    acc_memcpy_to_device(d_data, h_data, SIZE * sizeof(float));

    /* Check data on device through host_data and if_present clause*/
    #pragma acc host_data use_device(d_data) if_present
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (h_data[i] != d_data[i])
            {
                err++;
                printf("Error: element %d is %f, but expected %f\n", i, d_data[i], h_data[i]);
            }
        }
    }

    /* Cleanup */
    acc_free(d_data);
    free(h_data);

    return err;
}