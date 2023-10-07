#include "acc_testsuite.h"
#ifndef T1
//T1:acc is present,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    int *data;
    data = (int *)malloc(n * sizeof(int));
    int bytes = n * sizeof(int);

    for (int x = 0; x < n; ++x){
        data[x] = rand() % n;
    }

    #pragma acc enter data copyin(data[0:n])
    #pragma acc parallel present(data[0:n])
    {
    }

    if (acc_is_present(data, bytes) == 0){
        err = 1;
    }

    #pragma acc exit data delete(data[0:n])
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