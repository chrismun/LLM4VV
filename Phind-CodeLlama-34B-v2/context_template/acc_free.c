#include "acc_testsuite.h"
#ifndef T1
//T1:acc free,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    for (int i = 0; i < 20; i++){
        int size = rand() % (1024 * 1024);
        void *data_dev = acc_malloc(size);
        if (data_dev == NULL){
            err = 1;
            break;
        }
        acc_free(data_dev);
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