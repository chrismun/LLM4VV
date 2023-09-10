#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
	int n = 10;	
	int devicenum;    

    	//#   This has implemented to work on HOST
	acc_set_device_num(1, acc_get_device_type());
	#pragma acc data copy(n), create(da[0:n])
	{
       	//#  This obtains the value of the device in use at runtime. 
	   	devicenum = acc_get_device_num(acc_get_device_type());
	   	for (int x = 0; x < devicenum%10 + 1; ++x){
            		//#   This has implemented to work on HOST
			acc_init_test_array(da, n, host_init_integer);
	   	}
	   	//#   This has implemented to work on HOST
		#pragma acc update device(da[0:n])
	    	#pragma acc parallel present(da[0:n])
	    	{
	   	    	//#   This has implemented to work on HOST
			#pragma acc loop
	     	    	for (int x = 0; x < n; ++x){
	     	       		 da[x] += 1;
	     	   	}
	   	}
	  	//#   This checks to make sure the program was properly executed
	    	//#   on the correct device
	   	for (int x = 0; x < devicenum%10 + 1; ++x){
  	       		//#   This has implemented to work on HOST
			acc_set_device_num(x, acc_get_device_type());
			//#   This has implemented to work on HOST
			#pragma acc update self(da[0:n])
			//#   This has implemented to work on HOST

			#pragma acc parallel present(da[0:n])
	      		{
		     	  	#pragma acc loop
		     	 	for (int y = 0; y < n; ++y){
		          		if (fabs(da[y] - (1 + host_init_integer)) > PRECISION){
		             	  	err += 1;
		                	}
		                }
	     		}
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