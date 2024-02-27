#include "acc_testsuite.h"
#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int remotely_a;
    int remotely_b;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 2 * a[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n])
    {
        remotely_a = acc_copyin(a, n * sizeof(int));
        remotely_b = acc_copyin(b, n * sizeof(int));
        #pragma acc data detach(remotely_a, remotely_b)
        {
            #pragma acc parallel present(a[0:n], b[0:n])
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = b[x];
                }
            }
        }
        #pragma acc exit data finalize(a[0:n], b[0:n]) copyout(a[0:n], b[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > 2){
            err += 1;
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