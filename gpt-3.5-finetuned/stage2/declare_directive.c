#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = malloc(n * sizeof(int));
    int *b = malloc(n * sizeof(int));
    int *c = malloc(n * sizeof(int));
	real_t *devrand;

    //Declare local copies are as pointers to the pointers and allocate the data on the target device
	#pragma acc declare create(a[0:n], b[0:n]) copyout(c[0:n]) 
	{
		//Inside the region, the variables a and b are created on our device and 
		//will persist within a data region due to the declare directive

		devrand = acc_create(devrand);
		//Do some OpenACC Stuff
   

		#pragma acc parallel
		{
			#pragma acc loop
			for (int x = 0; x < n; ++x){
				a[x] = devrand[2 * x];
			}
		    #pragma acc loop
			for (int x = 0; x < n; ++x){
				b[x] = devrand[2 * x + 1];
			}
			#pragma acc loop
			for (int x = 0; x < n; ++x){
				c[x] = a[x] + b[x];
			}
		}
	}

	free(a);
	free(b);
	free(c);	

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