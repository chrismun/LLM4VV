#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(present_data){
        real_t * a = (real_t *)malloc(n * sizeof(real_t));
        real_t * b = (real_t *)malloc(n * sizeof(real_t));
    
        for (int x = 0; x < n; ++x){
            a[x] = 0.0;
            b[x] = 0.0;
        }
    
        #pragma acc enter data copyin(a[0:n]) async(1)
        for (int x = 0; x < iteration_multiplier; ++x){
            #pragma acc data copyin(b[0:n]) if_present(a[0:n])
            {
                #pragma acc parallel async(1) wait
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        a[y] = 1.0;
                    }
                }
                #pragma acc parallel async(1) 
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        a[y] += 1.0;
                    }
                }
    
                #pragma acc parallel wait(1)
                {
                    #pragma acc loop
                    for (int y = 0; y < n; ++y){
                        b[y] += a[y];
                    }
                }
            }
        }
        #pragma acc exit data copyout(b[0:n]), delete(a[0:n])
    
        for (int x = 0; x < iteration_multiplier; ++x){
            for (int y = 0; y < n; ++y){
                a[y] += 1;
            }
        }
    
        for (int x = 0; x < n; ++x){
            if (fabs(a[x] - b[x]) > PRECISION){
                err += 1;
                break;
            }
        }
        free(a);
        free(b);
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