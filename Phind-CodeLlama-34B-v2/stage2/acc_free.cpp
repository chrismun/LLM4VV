#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

#ifndef T1
/*T1:acc free,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *data_dev;
    size_t size = 10 * sizeof(int);
    data_dev = (int *)acc_malloc(size);
    assert(data_dev != NULL);

    if(acc_free(data_dev) != 0){
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