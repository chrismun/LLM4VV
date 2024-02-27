#include<assert.h>
#include<omp.h>

#ifndef T1
//T1:acc get device type,V:2.7-3.3
int test1(){
    int err = 0;

 	if (acc_get_device_type() != acc_device_none){ 
        int current_device = 0;
#pragma omp target
  {
          current_device = acc_get_device_type();
      if (current_device != 1)
        err += 1;
    }
    if (acc_get_device_type() != 1){
	assert(0);
      	err += 1;
    }
	}

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}