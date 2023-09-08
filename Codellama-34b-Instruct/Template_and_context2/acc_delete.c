#include "acc_testsuite.h"

#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate some memory on the device
    void *data = acc_malloc(1024);

    // Copy some data to the device
    acc_copyin(data, 1024);

    // Delete the data on the device
    acc_delete(data, 1024);

    // Check that the data has been deleted
    if (acc_is_present(data, 1024) != 0) {
        err = 1;
    }

    // Free the memory on the device
    acc_free(data);

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