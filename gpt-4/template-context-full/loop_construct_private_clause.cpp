#include "acc_testsuite.h"

#ifndef T1
/*T1:loop construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int n = 1024;
    int a[n], b[n], c[n];
    for(int i=0; i<n; i++){
        a[i] = i;
        b[i] = rand() % n;
        c[i] = rand() % n;
    }
    
    #pragma acc parallel copyin(b[:n],c[:n]) copy(a[:n])
    {
        #pragma acc loop private(tmp)
        for(int j = 0; j < n; j++) {
            int tmp = b[j] + c[j];
            a[j] = a[j] + tmp;
        }
    }
    // Validation
    for (int i = 0; i < n; ++i) {
        if (a[i] != i + b[i] + c[i]){
            err = 1;
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