#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:host_data construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int*a = (int*)malloc(100*sizeof(int));
    int*b = (int*)malloc(100*sizeof(int));

    for(int i = 0; i < 100; i++){
        a[i] = rand()%100;
        b[i] = rand()%100;
    }

    int condition = 1; //Setting condition

    // OpenACC directve
    #pragma acc host_data use_device(a, b) if(condition)
    {
        if(!acc_is_present(a, 100*sizeof(int)) || !acc_is_present(b, 100*sizeof(int))){
            err = 1;
        }
    }

    free(a);
    free(b);
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