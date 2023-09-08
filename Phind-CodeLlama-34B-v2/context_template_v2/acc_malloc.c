#include "acc_testsuite.h"
#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    size_t bytes = 1024;
    void *host_ptr = acc_malloc(bytes);

    if (host_ptr == NULL) {
        err = 1;
    }

    acc_free(host_ptr);
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