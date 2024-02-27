#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
  	
  	int n = 10;
  	int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
      
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc enter data create(c[0:n])
    #pragma acc data copyin(a[0:n], b[0:n])
    {
    	// Async kernel
    	#pragma acc parallel loop present(a[0:n], b[0:n], c[0:n]) async(1)
    	for (int x = 0; x < n; ++x){
        	c[x] = a[x] + b[x];
    	}
    	// Async wait
    	acc_wait_async(1, 2);
    	// Async kernel
    	#pragma acc parallel loop present(a[0:n], b[0:n], c[0:n]) async(1)
      	for (int x = 0; x < n; ++x){
        	c[x] += a[x] + b[x];
      	} 
    }
    #pragma acc exit data delete(c[0:n])

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