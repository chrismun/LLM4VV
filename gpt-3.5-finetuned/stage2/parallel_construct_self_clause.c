#include "acc_testsuite.h"
#include <math.h>
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    int _n_ = 1024;
    srand(SEED);
    char *host = (char *)malloc(sizeof(char) * _n_);
    char *device = (char *)malloc(sizeof(char) * _n_);

    for (int x = 0; x < _n_; ++x){
        host[x] = 0;
    }

    #pragma acc data copy(device[0:_n_])
    {
        #pragma acc parallel loop self_clause
        for (int x = 0; x < _n_; ++x){
            device[x] = 1;
        }
    }

    for (int x = 0; x < _n_; ++x){
        if (device[x] != 1){
            err = 1;
        }
    }

    free(host);
    free(device);

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