#include "acc_testsuite.h"
#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int* a = (int *)malloc(n * sizeof(int));
    int holder = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 1;
    }
    #pragma acc data copy(a[0:n])
    {
        for (int x = 0; x < 10; ++x) {
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                a[x] += 1;
            } 
        }
    }

    for (int x = 0; x < n; ++x) {
        holder = holder + a[x];
    }
    if (holder != 11 * n){
        err = 1;
    }
    free(a);

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