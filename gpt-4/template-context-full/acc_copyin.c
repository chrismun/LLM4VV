#include "acc_testsuite.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifndef T1
/*T1:acc copyin,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    float* host_array = (float*) malloc(100 * sizeof(float));
	float* device_array = NULL;
    
  	for (int i = 0; i < 100; i++) {
    	host_array[i] = (float)rand() / (float)(RAND_MAX / 100.0);
  	}
  	
	device_array = (float*) acc_copyin(host_array, 100 * sizeof(float));

	if (device_array == NULL) {
    	fprintf(stderr, "acc_copyin failed\n");
    	err = 1;
	} 
	else {
    	#pragma acc parallel present(device_array[0:99])
    	{
    		for (int i = 0; i < 100; i++) {
        		if(fabs(device_array[i] - host_array[i]) > 1e-5) {
            		err = 1;
        		}
    		}
    	}
	}
    
    free(host_array);
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