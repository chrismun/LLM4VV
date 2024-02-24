#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Allocate memory
    void* ptr = acc_malloc(100);
    if (ptr == NULL) {
        err = 1;
    }

    // Free memory
    acc_free(ptr);

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