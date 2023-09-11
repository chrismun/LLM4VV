#include "acc_testsuite.h"

//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    void *data_dev = acc_malloc(sizeof(int));
    if (data_dev == NULL) {
        err = 1;
    }

    acc_free(data_dev);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}