#include "acc_testsuite.h"
#ifndef T1
/*T1:atomic construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));
    int *c = (int *)malloc(10 * sizeof(int));

    for (int x = 0; x < 10; ++x) {
        a[x] = rand() % 100;
        b[x] = rand() % 100;
    }

    #pragma acc parallel copy(a[0:10], b[0:10], c[0:10])
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x) {
            #pragma acc atomic capture
            {
                c[x] = a[x];
                a[x] += b[x];
            }
        }
    }

    for (int x = 0; x < 10; ++x) {
        if (a[x] != c[x] + b[x]) {
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