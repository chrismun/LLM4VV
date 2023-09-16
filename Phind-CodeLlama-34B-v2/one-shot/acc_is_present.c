#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(){
    int acc_present = acc_get_num_devices(acc_device_not_host);

    if(acc_present == -1){
        printf("OpenACC is not present on this system.\n");
        return 1;
    }
    else{
        printf("OpenACC is present on this system.\n");
        return 0;
    }
}