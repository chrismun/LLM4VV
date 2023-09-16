#include "openacc.h"
#include <stdio.h>

int main()
{
    // Initialize array
    int N = 1000;
    float a[N];

    // Initialize acc_device_t
    acc_device_t my_device;

    // Get device type
    my_device = acc_get_device_type();

    // Set device type
    acc_set_device_type(my_device);

    // Check current device
    int my_device_num = acc_get_device_num(my_device);
    printf("Current Device :%d\n", my_device_num);

    // Set up loop for testing OpenACC auto clause
    #pragma acc parallel loop auto
    for (int i = 0; i < N; i++){
        a[i] = i * 2.0f;
    }

    // Sum over arrays to check results
    float sum = 0.0f;
    for(int i=0; i<N; i++){
        sum+=a[i];
    }
    printf("Total Sum:%f\n", sum);

    return 0;
}