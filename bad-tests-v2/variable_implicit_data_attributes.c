#include "acc_testsuite.h"
#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int device = 0;
    int errors[10];
    int _n = n;

    for (int x = 0; x < _n; ++x){
        a[x] = 1;
    }

    while(_n > 1){
        errors[device] = 0;
        #pragma acc data copy(a[0:_n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for(int x = 0; x < _n; ++x){
                    a[x] = a[x] + 1;
                }
            }
        }

        for (int x = 0; x < _n/2; ++x){
            if (a[x] != 2){
                errors[device] += 1;
            }
        }
        for (int x = _n/2; x < _n; ++x){
            if (a[x] != 1){
                errors[device] += 1;
            }
        }

        _n = _n/2;
        device = device + 1;
    }

    for (int x = 0; x < device + 1; ++x){
        if (errors[x] != 0){
            err += 1;
        }
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