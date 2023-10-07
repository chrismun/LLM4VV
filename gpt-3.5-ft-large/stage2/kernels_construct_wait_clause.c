#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int async_total = 1;
    #pragma acc data copyin(async_total) pcreate(A[0:10])
    for (int x = 0; x < async_total; ++x){
        int * A = (int *)malloc(10 * sizeof(int));
        #pragma acc parallel loop async(x) present(A[0:10])
        for (int y = 0; y < 10; ++y){
            A[y] = 1;
        }
        #pragma acc kernels loop wait
        for (int y = 1; y < 10; ++y){
            A[y] = A[y] + A[y-1];
        }
        #pragma acc enter data copyin(A[0:10]) async(x)
        for (int y = 0; y < 10; y++){
            if (A[y] != y + 1){
                err += 1;
            }
        }
        #pragma acc exit data copyout(A[0:10]) delete(A[0:10]) async(x)
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