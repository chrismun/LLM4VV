#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    unsigned short int *devtest1_1 = (unsigned short int *)malloc(n * sizeof(unsigned short int));
    unsigned short int *hosttest1_1 = (unsigned short int *)malloc(n * sizeof(unsigned short int));
    unsigned short int *devtest1_2 = (unsigned short int *)malloc(n * sizeof(unsigned short int));
    unsigned short int *hosttest1_2 = (unsigned short int *)malloc(n * sizeof(unsigned short int));
    unsigned short int *devtest1_3 = (unsigned short int *)malloc(n * sizeof(unsigned short int));
    unsigned short int *hosttest1_3 = (unsigned short int *)malloc(n * sizeof(unsigned short int));

    for (int x = 0; x < n; ++x){
        hosttest1_1[x] = (unsigned short int)rand() / (real_t)(RAND_MAX / 65535);
        hosttest1_2[x] = (unsigned short int)rand() / (real_t)(RAND_MAX / 65535);
        hosttest1_3[x] = 0;
    }

    #pragma acc enter data copyin(devtest1_1[0:n], devtest1_2[0:n])
    #pragma acc data copyout(devtest1_1[0:n], devtest1_2[0:n]) present(devtest1_1[0:n], devtest1_2[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                devtest1_1[x] = 2 * devtest1_1[x];
            }
            #pragma acc loop if(n>256)
            for (int x = 0; x < n; ++x){
                devtest1_2[x] = 2 * devtest1_2[x];
            }
        }
    }
    #pragma acc exit data copyout(hosttest1_1[0:n], hosttest1_2[0:n])
    for (int x = 0; x < n; ++x){
        if (hosttest1_1[x] != devtest1_1[x]){
            err += 1;
        }
        if (hosttest1_2[x] != devtest1_2[x]){
            err += 1;
        }
    }

    free(hosttest1_1);
    free(hosttest1_2);
    free(hosttest1_3);
    free(devtest1_1);
    free(devtest1_2);
    free(devtest1_3);

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