#include "acc_testsuite.h"
#include <stdlib.h>
#include <math.h>

#ifndef T1
/*T1:parallel,num_gangs,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int gang_size = 1024;
    unsigned int num_gangs = 32;

    float * a = (float *)malloc(32 * 1024 * sizeof(float));
    float * b = (float *)malloc(32 * 1024 * sizeof(float));

    for(unsigned int i = 0; i < 32*1024; i++){
        a[i] = rand() / (float)RAND_MAX;
        b[i] = a[i];
    }

#pragma acc parallel num_gangs(num_gangs) vector_length(gang_size)
    {
#pragma acc loop gang
        for(unsigned int i = 0; i < 32*1024; i++){
            a[i] = sinf(a[i]) + cosf(a[i]);
        }
    }

    for(unsigned int i = 0; i < 32*1024; i++){
        b[i] = sinf(b[i]) + cosf(b[i]);
        if(fabs(a[i] - b[i] > 1e-5){
            err = 1;
        }
    }

    free(a);
    free(b);
 
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