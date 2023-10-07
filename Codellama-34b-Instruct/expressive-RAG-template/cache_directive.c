#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc cache(device)
    {
        int *a = (int *)malloc(sizeof(int) * 10);
        int *b = (int *)malloc(sizeof(int) * 10);
        int *c = (int *)malloc(sizeof(int) * 10);

        #pragma acc data copy(a[0:10], b[0:10], c[0:10])
        {
            for (int i = 0; i < 10; i++) {
                a[i] = i;
                b[i] = i * 2;
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc cache(a[0:10], b[0:10], c[0:10])
        {
            for (int i = 0; i < 10; i++) {
                a[i] = i * 2;
                b[i] = i * 3;
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc cache(a[0:10], b[0:10], c[0:10])
        {
            for (int i = 0; i < 10; i++) {
                a[i] = i * 3;
                b[i] = i * 4;
                c[i] = a[i] + b[i];
            }
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