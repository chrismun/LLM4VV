#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc serial num_workers(16)
	{
		// complete test here
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