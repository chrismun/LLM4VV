#ifndef T1
//T1:construct-independent,init,devonly-3.0
int test1(){
  int err = 0;

  if (acc_get_device_type() != acc_device_none){
    #pragma acc init device_type(none)
  }
  else{
    err += 1;
  }

  return err;
}
#endif

#ifndef T2
//T2:construct-independent,init,devonly-3.0
int test2(){
  int err = 0;
  int device_num;

  device_num = acc_get_device_num(acc_get_device_type());

  if (acc_get_device_type() != acc_device_none){
    #pragma acc init device_num(device_num)
  }
  else{
    err += 1;
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
#ifndef T2
  	failed = 0;
  	for (int x = 0; x < NUM_TEST_CALLS; ++x){
    	    failed = failed + test2();
  	}
  	if (failed != 0){
    	    failcode = failcode + (1 << 1);
  	}
#endif
  	return failcode;
}