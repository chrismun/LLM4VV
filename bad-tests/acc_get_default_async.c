#include "acc_testsuite.h"
#ifndef T1
/*T1:acc get default async,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int default_async = acc_get_default_async();

    //The default value of acc-default-async-var is acc_async_noval(-1)
    if(default_async != -1){   
        err = 1;
    }

    //Try setting acc-default-async-var to a valid value using acc_set_default_async
    acc_set_default_async(1);

    //Now check again
    default_async = acc_get_default_async();
    
    if(default_async != 1){
        err = 1;
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