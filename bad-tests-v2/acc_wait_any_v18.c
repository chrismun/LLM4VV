#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    int asyncID;
    srand(SEED);

    real_t *host_data = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_data2 = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_result = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_result2 = (real_t *)malloc(n * sizeof(real_t));
    real_t *dev_data;
    real_t *dev_data2;
    real_t *dev_result;
    real_t *dev_result2;

    for (int x = 0; x < n; ++x){
        host_data[x] = rand() / (real_t)(RAND_MAX / 10);
        host_data2[x] = rand() / (real_t)(RAND_MAX / 10);
        host_result[x] = 0;
        host_result2[x] = 0;
    }
    #pragma acc data copyin(host_data[0:n], host_data2[0:n]) copyout(host_result[0:n], host_result2[0:n])
    {
        #pragma acc enter data create(dev_data[0:n], dev_data2[0:n], dev_result[0:n], dev_result2[0:n])
        #pragma acc update device(dev_data[0:n], dev_data2[0:n]) async(0)
        #pragma acc update device(dev_data[0:n], dev_data2[0:n]) async(1)
        #ifdef OPENMP
        #pragma omp parallel
        {
        #pragma omp single
        {
        }
        }
        #endif
    }

    for (int x = 1; x < n; ++x){
        host_result[x] = host_data[x] + host_data[x-1];
        host_result2[x] = host_data2[x] + host_data2[x-1];
    }

    #pragma acc data copyin(host_data[0:n], host_data2[0:n]) copyout(dev_result[0:n], dev_result2[0:n])
    {
        #pragma acc wait
        for (int x = 1; x < n; ++x){
            #pragma acc host_data(present, dev_result [x]) if(asyncID >0)
            {
                if (asyncID > 0){
                    fprintf(stderr, "Encountered more than one async IDs.");
                    asyncSuccess = 0;
                }
                asyncID = 0;
            }
            #pragma acc host_data(present, dev_result2 [x]) if(asyncID >1)
            {
                if (asyncID > 1){
                    fprintf(stderr, "Encountered more than two async IDs.");
                    asyncSuccess = 0;
                }
                asyncID = 1;
            }
            fprintf(stderr, "passing pointer to dev_result\n");
            #pragma acc wait any(asyncID)
            #pragma acc parallel loop async(x)
            for (int y = x; y < n; ++y){
                dev_result[y] = dev_data[y] + dev_data[y-1];
            }
            #pragma acc parallel loop async(x)
            for (int y = x; y < n; ++y){
                dev_result2[y] = dev_data2[y] + dev_data2[y-1];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(host_result[x] - dev_result[x]) > PRECISION){
            err += 1;
        }
        if (fabs(host_result2[x] - dev_result2[x]) > PRECISION){
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