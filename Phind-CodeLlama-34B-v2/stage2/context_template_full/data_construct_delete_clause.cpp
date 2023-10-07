#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct delete clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(10 * sizeof(int));
    int *d_a = NULL;

    #pragma acc enter data copyin(a[0:10])
    #pragma acc enter data create(d_a[0:10])

    #pragma acc parallel present(a[0:10], d_a[0:10])
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x) {
            d_a[x] = a[x] * 2;
        }
    }

    #pragma acc exit data delete(d_a[0:10])

    #pragma acc exit data delete(a[0:10])

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