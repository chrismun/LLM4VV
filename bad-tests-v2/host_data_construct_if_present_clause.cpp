#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(present_or_copyin(host_data, host_data_array[0:10*PRE_LOOP_ITERATIONS])))
        for(int x = 0; x < 10 * PRE_LOOP_ITERATIONS; ++x)
            host_data_array[x] = 0;

    real_t * a = new real_t[10 * PRE_LOOP_ITERATIONS];

    for(int x = 0; x < 10 * PRE_LOOP_ITERATIONS; ++x){
        a[x] = getRandomNumber<real_t>(.1, 1);
    }

    if(present_or_copyin(a[0:10*PRE_LOOP_ITERATIONS]))
        for(int x = 0; x < 10 * PRE_LOOP_ITERATIONS; ++x)
            if(a[x] + PRE_LOOP_ITERATIONS > a[x] || a[x] - PRE_LOOP_ITERATIONS > a[x])
                a[x] = 0.0;

    #pragma acc data device_data a[0:10*PRE_LOOP_ITERATIONS]
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for(int x = 0; x < PRE_LOOP_ITERATIONS; ++x){
                #pragma acc loop
                for(int y = 0; y < 10; ++y){
                    #pragma acc loop seq
                    for(int z = 0; z < x; ++z){
                        a[x * 10 + y] += a[z * 10 + y];
                    }
                }
            }
        }
    }

    if(present_or_copyout(a[0:10*PRE_LOOP_ITERATIONS]))
        for(int x = 0; x < PRE_LOOP_ITERATIONS; ++x){
            for(int y = 0; y < 10; ++y){
                if(a[x * 10 + y] < PRE_LOOP_ITERATIONS - 1){
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