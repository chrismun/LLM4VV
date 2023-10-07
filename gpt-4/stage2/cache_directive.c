#include "acc_testsuite.h"
#ifndef T1
/*T1:cache directive,V:2.0-2.7*/
int test1(){

    int err = 0;
    int size = 1024;
    int *a = (int*) malloc(sizeof(int)*size);
    if (a == NULL){
        err = 1;
    }

    // Set data on array
    for(int i = 1; i<size; i++){
        a[i] = i;
    }

    int sum = 0;
    #pragma acc parallel copy(a[0:size])
    {
        #pragma acc loop reduction(+:sum)
        #pragma acc cache(a[0:size])
        for(int i = 0; i<size; i++){
            sum += a[i];
        }
    }

    // verify data on host
    int host_sum = 0;
    for(int i = 0; i<size; i++){
        host_sum += a[i];
    }
    if (sum != host_sum){
        err = 1;
    }

    free(a);
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