#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct attach clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    #pragma acc enter data attach(a[0:n], b[0:n], c[0:n])
    #pragma acc data attach(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel
        {
            int i = 0;
            #pragma acc loop
            for (i = 0; i < n; i++) {
                a[i] = b[i] + c[i];
            }
        }
    }
    #pragma acc exit data delete(a[0:n], b[0:n], c[0:n])

    for (int x = 0; x < n; ++x) {
        if (a[x] != b[x] + c[x]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

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