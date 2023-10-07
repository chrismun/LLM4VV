#include "acc_testsuite.h"
#ifndef T1
/*T1:acc is present,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *data = (int *)malloc(10 * sizeof(int));
    int query = acc_is_present(data, 10 * sizeof(int));

    if (query == 0){
        err = 1;
    }

    free(data);

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