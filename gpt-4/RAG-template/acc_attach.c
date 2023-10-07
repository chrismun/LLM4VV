#include "acc_testsuite.h"

#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    int* rand_num;

    srand(SEED);

    #pragma acc data create(rand_num[1])
    {
        #pragma acc parallel loop
        for(int i=0; i<1; i++){
            rand_num[i] = rand();
        }

        #pragma acc exit data copyout(rand_num[1])

        #pragma acc enter data attach(rand_num[1])

        #pragma acc parallel loop
        for(int i=0; i<1; i++){
            if(rand_num[i] != rand_num[i]){
                err = 1;
            }
        }

        #pragma acc exit data detach(rand_num[1])
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