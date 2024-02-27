#include "acc_testsuite.h"
#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    {    
        int *a = (int *)malloc(n * sizeof(int));
        int *b = (int *)malloc(n * sizeof(int));

        for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
        }

        #pragma acc data copy(a[0:n]) copy(b[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                a[x] += 1;
                }
            }
            
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                b[x] += 1;
                }
            }
        }

        for (int x = 0; x < n; ++x){
            if(a[x] != 2){
            err += 1;
            }
            if(b[x] != 3){
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