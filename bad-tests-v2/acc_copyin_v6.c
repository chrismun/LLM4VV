#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>

//To test acc_copyin
int test(){
    int err = 0;
    int a = 5;
    int* d_a;

    srand(time(NULL));

    #pragma acc enter data create(a)
    d_a = acc_copyin(&a, sizeof(int));

    #pragma acc parallel present(a) copyin(d_a[0:1])
    {
        if(d_a[0]!=a){
            err = 1;
        }
    }

    #pragma acc exit data delete(a)
    acc_free(d_a);

    if(err){
        return 1;
    }

    return 0;
}

int main(){
    int failcode = 0;
    int failed;
    int NUM_TEST_CALLS = 100;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}