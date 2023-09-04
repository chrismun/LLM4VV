#include "acc_testsuite.h"

int main(){
    int fail = 0;
    int num_devices = 0;

    #pragma acc init

    num_devices = acc_get_num_devices(acc_device_any);
    if(num_devices < 1){
        printf("Error: No OpenACC devices found\n");
        fail = 1;
    }
    else{
        printf("Number of OpenACC devices found: %d\n", num_devices);
    }

    #pragma acc shutdown

    return fail;
}