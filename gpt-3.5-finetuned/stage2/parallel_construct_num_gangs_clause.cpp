#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,loop,parallelism,combined-constructs,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #define NUM_GANGS 128
    int * a = new int[NUM_GANGS * PRESENT_LOOP_INDEX + 10];
    int * b = new int[NUM_GANGS * 10];
    real_t * num_gangs = new real_t[NUM_GANGS];

    for (int x = 0; x < NUM_GANGS * PRESENT_LOOP_INDEX + 10; ++x){
        a[x] = 0;
    }

    for (int x = 0; x < 10; ++x){
        b[x] = 1;
    }

    for (int x = 0; x < NUM_GANGS; ++x) {
        num_gangs[x] = 1;
    }

    #pragma acc data copyin(num_gangs[0:NUM_GANGS]) copy(a[0:NUM_GANGS * PRESENT_LOOP_INDEX + 10], b[0:NUM_GANGS * 10])
    {
        #pragma acc parallel num_gangs(NUM_GANGS)
        {
            #pragma acc loop gang
            for (int x = 0; x < NUM_GANGS; ++x){
                for (int y = 0; y < 10; ++y){
                    a[x * PRESENT_LOOP_INDEX + y] = b[x * 10 + y];
                }
            }
        }
    }

    for (int x = 0; x < NUM_GANGS * PRESENT_LOOP_INDEX + 10; ++x){
        if (x%PRESENT_LOOP_INDEX < 10){
            if (a[x] != 1){
                err += 1;
            }
        }
        else {
            if (a[x] != 0){
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