#include "acc_testsuite.h"
#include <stdlib.h>

//T1:kernels,loop,V:1.0-2.7
int test_num_gangs(){
    int err = 0;
    srand(SEED);
    int num_gangs = 16;  // Choose your number of gangs
    real_t * a = (real_t *)malloc(num_gangs * sizeof(real_t));
    real_t * b = (real_t *)malloc(num_gangs * sizeof(real_t));

    for (int x = 0; x < num_gangs; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:num_gangs])
    {
        #pragma acc kernels num_gangs(num_gangs)
        {
            #pragma acc loop
            for (int x = 0; x < num_gangs; ++x){
                b[x] = 2*a[x];
            }
        }
    }

    for (int x = 0; x < num_gangs; ++x){
        if (fabs(b[x] - 2*a[x]) > PRECISION){
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    //Call the test function for `num_tests` times and check if it fails any time 
    int num_tests = 50;

    for(int i=0; i<num_tests; i++){
        failcode += test_num_gangs();
    }

    if(failcode){
        printf("Test failed %d times out of %d\n", failcode, num_tests);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}