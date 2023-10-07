#include <stdio.h>
#include <openacc.h>

int main(){
    int device_num = acc_get_device_num(acc_device_default);
  
    if(device_num == -1){
        printf("Failed to get device number.\n");
        return 1;
    }
    
    printf("Device number: %d\n", device_num);
  
    return 0;