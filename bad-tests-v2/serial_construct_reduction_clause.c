#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
int test1(){
    int err = 0;
    srand(SEED);
    float *arr;
    float sum = 0, correctSum = 0;
    size_t n = 10000;
    
    arr = (float*) malloc(n * sizeof(float));
    
    for(size_t i = 0; i<n; ++i) {
        arr[i] = (float) rand() / RAND_MAX;
        correctSum += arr[i]; 
    }

#pragma acc data copy(arr[0:n])
{
    #pragma acc serial reduction(+:sum)
	for(size_t i = 0; i < n; ++i) {
		sum += arr[i];
	}
}
    if(sum != correctSum){
        err = 1;
    }

    free(arr);
    return err;
}
#endif

int main(){
    int fail_code = 0;
    int failed = 0;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        fail_code += 1;
    }
#endif
    
    return fail_code;
}