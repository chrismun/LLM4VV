#include "acc_testsuite.h"
#ifndef T1
/*T1:host_data construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
    }

    #pragma acc host_data use_device(a)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 2 * a[x];
            }
        }
    }

    int condition = 1;
    #pragma acc host_data if(condition) use_device(a)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] = 3 * a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (condition){
            if (a[x] != 3 * b[x]){
                err = 1;
                break;
            }
        }
        else{
            if (a[x] != 2 * b[x]){
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);

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