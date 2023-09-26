#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:data present clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int *host_array;
    int *dev_array;
    srand(SEED);

    host_array = (int*)malloc(10*sizeof(int));

    for(int i = 0; i < 10; i++){
        host_array[i] = i;
    }
    
    #pragma acc enter data create(host_array[0:10])
    {
        #pragma acc parallel present(host_array)
        {
            dev_array = host_array;

            for(int i = 0; i < 10; i++){
                dev_array[i] = i+1;
            }
        }
        
        #pragma acc exit data copyout(host_array[0:10])
        
        for(int i = 0; i < 10; i++){
            if(host_array[i] != i+1){
              err = 1;
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