#include "acc_testsuite.h"
#ifndef T1
/*T1:loop construct seq clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int a[1000], b[1000], c[1000];
    for(int i=0; i<1000; i++) {
        a[i] = rand()%1000;
        b[i] = rand()%1000;
        c[i] = 0;
    }

    #pragma acc parallel loop seq 
    for(int i=0; i<1000; i++)
        c[i] = a[i] + b[i];

    for(int i=0; i<1000; i++)
        if(c[i] != a[i] + b[i])
            err = 1;

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