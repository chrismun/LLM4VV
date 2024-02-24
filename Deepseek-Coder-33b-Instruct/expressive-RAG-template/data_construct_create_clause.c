#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:data construct create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    #pragma acc data create(a[0:n], b[0:n])
    {
        #pragma acc parallel loop
        for(int i = 0; i < n; i++) {
            a[i] = i;
            b[i] = i;
        }
    }

    for(int i = 0; i < n; i++) {
        if(a[i] != i || b[i] != i) {
            err = 1;
            break;
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