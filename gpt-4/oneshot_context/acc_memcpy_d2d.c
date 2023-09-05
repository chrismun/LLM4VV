#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1024
#define DEVICE_ONE 0
#define DEVICE_TWO 1

int main(int argc, char **argv)
{
    float *x = (float*) malloc(SIZE * sizeof(float));
    float *y = (float*) malloc(SIZE * sizeof(float));
    float *z = (float*) malloc(SIZE * sizeof(float));
    
    // Fill the arrays with some values
    for(int i = 0; i < SIZE; i++)
    {
        x[i] = i;
        z[i] = 0;
    }

    // Copy x[] to the device memory
    acc_init(acc_device_default);
    acc_set_device_num(DEVICE_ONE, acc_device_default);
    float *d_x = (float*) acc_malloc(SIZE * sizeof(float));
    acc_memcpy_to_device(d_x, x, SIZE * sizeof(float));

    // Copy from device to device (from DEVICE_ONE to DEVICE_TWO)
    acc_set_device_num(DEVICE_TWO, acc_device_default);
    float *d_y = (float*) acc_malloc(SIZE * sizeof(float));
    acc_memcpy_d2d(d_y, d_x, SIZE * sizeof(float), DEVICE_TWO, DEVICE_ONE);

    // Copy d_y[] back to host from DEVICE_TWO   
    acc_memcpy_from_device(y, d_y, SIZE * sizeof(float));
  
    // Verify the result
    for(int i = 0; i < SIZE; i++)
    {
        if(y[i] != x[i]) {
            printf("ERROR: y[%d] = %f, but expected %f\n", i, y[i], x[i]);
            return -1;
        }
    }
    // If there is no error, print a success message
    printf("SUCCESS: Data was copied correctly.\n");
   
    acc_free(d_x);
    acc_free(d_y);
    free(x);
    free(y);
    
    return 0;