#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_async = acc_get_num_async();
    if (num_async < 1) {
        printf("No async queues available, skipping test\n");
        return 0;
    }

    int default_async = acc_get_default_async();
    int new_async = rand() % num_async;
    acc_set_default_async(new_async);

    if (acc_get_default_async() != new_async) {
        err++;
        printf("Default async queue not set correctly\n");
    }

    acc_set_default_async(default_async); // reset to default

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