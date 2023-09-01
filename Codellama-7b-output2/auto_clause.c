#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(sizeof(int) * N);
    int *b = (int *)malloc(sizeof(int) * N);
    int *c = (int *)malloc(sizeof(int) * N);

    #pragma acc parallel present(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc loop auto
        for (int i = 0; i < N; i++){
            a[i] = i;
            b[i] = i * 2;
            c[i] = i * 3;
        }
    }

    #pragma acc parallel present(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc loop auto
        for (int i = 0; i < N; i++){
            if (a[i] != i || b[i] != i * 2 || c[i] != i * 3){
                err = 1;
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