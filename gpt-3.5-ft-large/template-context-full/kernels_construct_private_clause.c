#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

	int privately_kept = 0;
	int num_gangs = acc_get_num_gangs(acc_get_device_type());
	int gangs_loop = 2;

	#pragma acc parallel
	{
		#pragma acc loop gang private(privately_kept)
		for (int x = 0; x < gangs_loop; ++x){
			privately_kept = (7 << 25);
		}
	}
	if (privately_kept == (7 << 25)){
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
    return failcode;
}