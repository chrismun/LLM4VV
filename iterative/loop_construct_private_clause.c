#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int n = 100;
    const int div = 2;
    double a[n][n][n], b[n][n], c[n][n];
    double tmp;

    // Initialize arrays
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                a[i][j][k] = rand() % 100;
                b[j][k] = rand() % 100;
                c[j][k] = rand() % 100;
            }
        }
    }

    // OpenACC region
    #pragma acc data copyin(a, b, c) copyout(a)
    {
        #pragma acc parallel loop gang
        for(int k = 0; k < n; k++){
            #pragma acc loop worker private(tmp)
            for(int j = 0; j < n; j++){
                tmp = b[j][k] + c[j][k];
                #pragma acc loop vector
                for(int i = 0; i < n; i++){
                    a[i][j][k] = a[i][j][k] + tmp/div;
                }
            }
        }
    }

    // Check generated GPU code
    // TODO: Implement this part

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