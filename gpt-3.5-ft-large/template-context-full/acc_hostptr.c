#include "acc_testsuite.h"
#ifndef T1
//T1: acc hostptr,V:2.7-3.3
int test1(){
	int err = 0;
	srand(SEED);

    int *device_array = (int *)malloc(n * sizeof(int));
    int *host_array = (int *)malloc(n * sizeof(int));
    int *null_pointer = host_array;

    int errors = 0;
    #pragma acc data copy(device_array[0:n])
    {
	    #pragma acc parallel
        {
		    #pragma acc loop
			for (int x = 0; x < n; ++x){
			    device_array[x] = 1;
            }
        }
    }

	host_array[0] = device_array[0];
    null_pointer = acc_hostptr(device_array, 0);
    if (host_array[0] != null_pointer[0]){
    	err += 1;
    }
    #pragma acc enter data copyin(host_array[0:n])
    #pragma acc parallel
    {
        #pragma acc loop
	for (int x = 0; x < n; ++x){
	    device_array[x] = host_array[x];
        }
    }

    #pragma acc exit data delete(host_array[0:n]) copyout(device_array[0:n])

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