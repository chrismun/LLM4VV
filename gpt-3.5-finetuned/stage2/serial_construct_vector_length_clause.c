#include "acc_testsuite.h"
#ifndef T1
#define N 10
#define M 10

int test1(){
    int err = 0;
    srand(SEED);
    char *devicename = getenv("ACC_DEVICE_DEFAULT_NAME");
    char c[10][10];
    

    #pragma acc data create(c[0:N][0:M]) copyout(c[0:N])
    {
        #pragma acc serial vector_length(10)
        {
            #pragma acc loop
            for (int x = 0; x < N; ++x){
                for (int y = 0; y < M; ++y){
                    c[x][y] = 0;
                    for (int z = 0; z < 10; z++){
                        c[x][y] += z;
                    }
                }
            }
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