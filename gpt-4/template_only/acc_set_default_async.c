#include "openacc.h"
#include <stdio.h>

#define SIZE 1000

int main(){

  int fail = 0;
  int h_arr[SIZE], d_arr[SIZE];

  /* Initialize host array */
  for(int i = 0; i < SIZE; i++){
    h_arr[i] = i;
  }

  /* Set device data as per async clause */
  acc_set_device_num( 0, acc_async_noval );

  /* Copy data from host to device */
  acc_memcpy_to_device( d_arr, h_arr, SIZE * sizeof(int) );

  /* Wait for all async to complete */
  acc_wait_all();

  /* Copy data back from device to host */
  acc_memcpy_from_device( h_arr, d_arr, SIZE * sizeof(int) );

  /* Check if data are correct */
  for(int i = 1; i < SIZE; i++){
    if(h_arr[i] != i){
      printf("Test failed at index: %d. Expected : %d, but was: %d \n", i, i, h_arr[i]);
      fail = 1;
      break;
    }
  }

  /* Validate the result */
  if(fail == 0)
    printf("Test Passed!\n");
  else
    printf("Test Failed!\n");

  return fail;
}