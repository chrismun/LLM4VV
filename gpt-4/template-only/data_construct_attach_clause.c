#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* data = (int*) malloc(sizeof(int));
    *data = rand();

    int before = *data;

    #pragma acc enter data copyin(data[0:1])
    #pragma acc parallel present(data[0:1])
    {
        #pragma acc loop
        for(int i = 0 ; i < 1 ; i++){
            if(acc_is_present(data + i, sizeof(int)) == 0){
                err = 1;
                break;
            }
	    else {
		*data = *data * 2;
	    }
        }
    }
    #pragma acc exit data copyout(data[0:1])

    if (*data != before * 2){
        err = 1;
    }

    free(data);

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