#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234
#define RAND_MAX 1000
#define PRECISION 0.001

typedef double real_t;

int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(100 * 100 * 100 * sizeof(real_t));
    real_t * b = (real_t *)malloc(100 * 100 * 100 * sizeof(real_t));

    for (int x = 0; x < 100; ++x){
        for (int y = 0; y < 100; ++y){
            for (int z = 0; z < 100; ++z){
                a[x * 100 * 100 + y * 100 + z] = rand() / (real_t)(RAND_MAX / 10);
                b[x * 100 * 100 + y * 100 + z] = 0;
            }
        }
    }

    #pragma acc parallel num_gangs(10, 10, 10) copyin(a[0:100*100*100]) copyout(b[0:100*100*100])
    {
        #pragma acc loop
        for (int x = 0; x < 100; ++x){
            for (int y = 0; y < 100; ++y){
                for (int z = 0; z < 100; ++z){
                    b[x * 100 * 100 + y * 100 + z] = a[x * 100 * 100 + y * 100 + z] * 2;
                }
            }
        }
    }

    for (int x = 0; x < 100; ++x){
        for (int y = 0; y < 100; ++y){
            for (int z = 0; z < 100; ++z){
                if (fabs(b[x * 100 * 100 + y * 100 + z] - (a[x * 100 * 100 + y * 100 + z] * 2)) > PRECISION){
                    err += 1;
                }
            }
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