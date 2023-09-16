#include <openacc.h>
#include <stdio.h>

int main()
{
    // Number of devices 
    int numDevices = acc_get_num_devices( acc_device_default );
    printf("Total devices: %d\n", numDevices);

    for( int i = 0; i < numDevices; i++ )
    {
        // Set each device as current and check
        acc_set_device_num( i, acc_device_default );
        int currentDevice = acc_get_device_num( acc_device_default );

        if( i != currentDevice )
        {
            printf("Error! Expected current device to be %d but got %d \n", i, currentDevice);
            return 1; // Return error
        }
        else
        {
            printf("Current device successfully set to %d\n", currentDevice);
        }
    }

    return 0; // All tests passed
}