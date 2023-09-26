#include<stdio.h>
#include<openacc.h>

void test_acc_on_device(){
  if(acc_on_device(acc_device_none)){
    printf("We are not on any device\n");
  }
  if(acc_on_device(acc_device_default)){
    printf("We are on default device\n");
  }
  if(acc_on_device(acc_device_host)){
    printf("We are on host\n");
  }
  if(acc_on_device(acc_device_not_host)){
    printf("We are on not_host\n");
  }
}

int main(){
  test_acc_on_device();
  
  #pragma acc parallel 
  {
    test_acc_on_device();
  }
  
  return 0;
}