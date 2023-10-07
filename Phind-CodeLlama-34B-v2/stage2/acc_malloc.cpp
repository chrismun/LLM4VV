#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef T1
/*T1:acc malloc,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    size_t bytes = rand() % 10000 + 1;
    void* d_ptr = acc_malloc(bytes);

    if(d_ptr == nullptr){
        err = 1;
        std::cerr << "acc_malloc failed to allocate " << bytes << " bytes." << std::endl;
    } else {
        acc_free(d_ptr);
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