#include "acc_testsuite.h"
#ifndef T1
/*T1:loop construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * n * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * n * sizeof(real_t));
    real_t * tmp = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            b[x * n + y] = rand() / (real_t)(RAND_MAX / 10);
            c[x * n + y] = rand() / (real_t)(RAND_MAX / 10);
        }
    }

    #pragma acc data copy(a[0:n*n*n]), create(b[0:n*n], c[0:n*n])
    {
        #pragma acc parallel loop gang
        for (int k = 0; k < n; ++k){
            #pragma acc loop worker private(tmp)
            for (int j = 0; j < n; ++j){
                tmp[j] = b[j * n + k] + c[j * n + k];
                #pragma acc loop vector
                for (int i = 0; i < n; ++i){
                    a[i * n * n + j * n + k] = a[i * n * n + j * n + k] + tmp[j] / div;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            for (int z = 0; z < n; ++z){
                if (fabs(a[x * n * n + y * n + z] - (b[y * n + z] + c[y * n + z] + 1)) > PRECISION){
                    err = 1;
                }
            }
        }
    }

    free(a);
    free(b);
    free(c);
    free(tmp);

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