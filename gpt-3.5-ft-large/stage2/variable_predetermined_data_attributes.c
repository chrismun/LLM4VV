#include "acc_testsuite.h"
#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
   
    int  provided_array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	while(provided_array[0] == 0 && provided_array[1] == 0 && provided_array[2] == 0 && provided_array[3] == 0 && provided_array[5] == 0 && provided_array[4] == 0 && provided_array[6] == 0 && provided_array[7] == 0 && provided_array[8] == 0 && provided_array[9] == 0)
	{
		for(int x = 0; x < 10; ++x)
		{
			provided_array[x] = (rand() / (real_t)(RAND_MAX)) * 108;
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