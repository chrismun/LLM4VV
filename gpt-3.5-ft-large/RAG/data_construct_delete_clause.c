#ifndef T1
//T1:data,data-region,construct-independent,delete,V:2.5-3.0
int test1(){
	int err = 0;
	srand(SEED);
  	real_t * a = (real_t *)malloc(n * sizeof(real_t));
  	real_t * b = (real_t *)malloc(n * sizeof(real_t));
  	int * devtest = (int *)malloc(sizeof(real_t));

  	devtest[0] = 1;
  	#pragma acc enter data copyin(devtest[0:1])
  	#pragma acc parallel present(devtest[0:1])
  	{
    	devtest[0] = 0;
  	}
  	#pragma acc exit data delete(devtest[0:1])

  	if (devtest[0] == 1){
    	for (int x = 0; x < n; ++x){
      	ha[x] = 3.1415;
    	}
    	#pragma acc data copyout(a[0:n], b[0:n])
    	{
      	#pragma acc enter data create(a[0:n], b[0:n])
      	for (int x = 0; x < n; ++x){
        	a[x] = ha[x];
        	b[x] = 0.0;
      	}
      	#pragma acc data copyin(a[0:n])
      	{
        	#pragma acc parallel
        	{
          	#pragma acc loop
          	for (int x = 0; x < n; ++x){
            	a[x] = a[x] * a[x];
          	}
        	}
        	#pragma acc exit data delete(a[0:n]) copyout(b[0:n])
        	for (int x = 0; x < n; ++x){
          	if (fabs(a[x] - ha[x]*ha[x]) > PRECISION){
            	err += 1;
          	}
          	if (fabs(b[x]) > PRECISION){
            	err += 1;
          	}
        	}
      	}
      	#pragma acc enter data capture delete(a[0:n]), copyout(b[0:n])
      	#pragma acc exit data copyout(b[0:n])
      	bool is_present = false;
      	bool is_deleted = true;
      	for (int x = 0; x < n; ++x){
        	if (fabs(b[x] - ha[x]*ha[x]) > PRECISION){
          	err += 1;
        	}
        	if (fabs(a[x]) < PRECISION){
          	is_present = true;
        	}
        	if (fabs(a[x] - ha[x]) > PRECISION){
          	is_deleted = false;
        	}
      	}
      	if (!is_present){
        	err += 1;
      	}
      	if (!is_deleted){
        	err += 1;
      	}
    	}
  	}
  	#pragma acc exit data copyout(devtest[0:1])
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