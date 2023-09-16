#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234
#define RAND_MAX 1000
#define PRECISION 0.0001

int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(10 * sizeof(int));
    int *b = (int *)malloc(10 * sizeof(int));

    for (int x = 0; x < 10; ++x){
        a[x] = rand() % RAND_MAX;
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:10])
    {
        #pragma acc kernels copyout(b[0:10])
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        if (b[x] != a[x]){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}