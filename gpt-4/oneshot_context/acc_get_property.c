#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {

  int dev_num;
  acc_device_t dev_type;
  acc_device_property_t property;

  /* Set the device number and device type */
  dev_num = 0;
  dev_type = acc_device_nvidia;

  /* Check if the device type is supported */
  if (acc_get_num_devices(dev_type) == 0) {
    printf("No device of type %d is available.\n", dev_type);
    exit(-1);
  }

  /* Get the total memory size on the device */
  property = acc_property_memory;
  printf("Total memory size on device %d: ", dev_num);
  printf("%lu bytes\n", acc_get_property(dev_num, dev_type, property));

  /* Check if the device supports shared memory */
  property = acc_property_shared_memory_support;
  int sharedMemSupport = acc_get_property(dev_num, dev_type, property);
  if(sharedMemSupport != 0)
     printf("Device supports sharing memory with the local thread\n");

  /* Get the name, vendor, and driver of the device */
  printf("Device name: %s\n", acc_get_property_string(dev_num, dev_type, acc_property_name));
  printf("Device vendor: %s\n", acc_get_property_string(dev_num, dev_type, acc_property_vendor));
  printf("Device driver: %s\n", acc_get_property_string(dev_num, dev_type, acc_property_driver));

  return 0;
}