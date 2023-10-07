#include "acc_testsuite.h"
#ifndef T1
//T1: acc attach,V:2.7-3.3
int test1(){
	int err = 0;
	//host copies of arrays
    int array[NUM_DEVICES][10];

    //Initialization
    for (int x = 0; x < NUM_DEVICES; ++x){
    	for (int y = 0; y < 10; ++y){
    		array[x][y] = rand() / (real_t)(RAND_MAX / 10);
    	}
    }

    #pragma acc data copy(array[0:NUM_DEVICES][0:10])
    {
    	#pragma acc parallel num_gangs(NUM_DEVICES) 
    	{
    		//Attaching arrays on each device individually
    		#pragma acc loop gang present(array)
    		for (int x = 0; x < NUM_DEVICES; ++x){
    			attaching_a_ptr_acc_attach(array[x]);
    		}
    		#pragma detach array
    	}
    }

    #pragma acc data copy(array[0:NUM_DEVICES][0:10])
    {
    	#pragma acc parallel num_gangs(NUM_DEVICES) 
    	{
    		#pragma acc loop gang present(array)
    		for (int x = 0; x < NUM_DEVICES; ++x){
    			if (!testing_operator_or_scoring_operator_clause(array[x], SEED / 2, "*")){
    				err = 1;
    				break;
    			}
    		}
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