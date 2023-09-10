#include "acc_testsuite.h"
#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t function_value = 0;
    real_t a[10][10];

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 10; ++y){
            a[x][y] = rand() / (real_t)(RAND_MAX / 10);
        }
    }

    #pragma acc data copy(a[0:10][0:10])
    {
        #pragma acc kernels 
        {
            #pragma acc cache(a[0:10][0])
            for (int x = 1; x < 10; ++x){
                function_value += a[x][0];
            }
            for (int x = 0; x < 10; ++x){
                for (int y = 1; y < 10; ++y){
                    a[x][y] = function_value;
                }
            }
        }
    }
    function_value = 0;
    for (int x = 1; x < 10; ++x){
        function_value += a[x][0];
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 1; y < 10; ++y){
            if (a[x][y] + PRECISION < function_value || a[x][y] - PRECISION > function_value){
                err += 1;
            }
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