#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,parallel,if,loop,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a = 0;
    int b[NUM GANGS] = {0};

    #pragma acc data copyin(a) copyout(b)
    {
        #pragma acc parallel
        {
            int local_a = 0;

            #pragma acc loop reduction(+:local_a)
            for (int x = 0; x < n; ++x){
                local_a += 1;
            }

            #pragma acc barrier

            #pragma acc loop
            for (int x = 0; x < NUM GANGS; ++x){
                b[x] = local_a;
            }
        }
    }

    for (int x = 0; x < NUM GANGS; ++x){
        if (b[x] != n){
            err += 1;
            break;
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
    for (int x = 0; x < NUM TEST CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}