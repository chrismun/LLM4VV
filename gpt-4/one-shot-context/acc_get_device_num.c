#include <stdio.h>
#include <openacc.h>

int main(int argc, char *argv[]) {

    // Get the number of all available devices
    int numDevices = acc_get_num_devices(acc_device_default);

    printf("Number of available devices: %d\n", numDevices);

    // Check if any devices are available
    if(numDevices > 0){
    
        // Iterate through each device
        for(int i=0; i<numDevices; i++){

            // Set device
            acc_set_device_num(i, acc_device_default);
            
            // Get and print the current device number for verification
            int deviceNum = acc_get_device_num(acc_device_default);

            printf("Current device number: %d\n", deviceNum);

            // Check if actual and expected device numbers match
            if(deviceNum != i){
                printf("acc_get_device_num() test failed.\n");
                return 1;
            }
        }
    }
    else{
        printf("No OpenACC capable devices available. Can't run the test.\n");
        return 1;
    }

    printf("acc_get_device_num() executed succesfully on all devices.\n");
    return 0;
}