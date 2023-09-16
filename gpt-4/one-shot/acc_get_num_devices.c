#include <stdio.h>
#include <openacc.h>

int main() {
   int result_code = 0;
   
   int num_devices = acc_get_num_devices(acc_device_all);

   if (num_devices <= 0) {
       printf("No devices found.\n");
       result_code = 1; 
   } else {
       printf("Number of devices: %d\n", num_devices);
   }

   return result_code;
}