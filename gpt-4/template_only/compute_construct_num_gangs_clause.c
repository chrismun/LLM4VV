#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_gangs clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs;
    int sum;

    #pragma acc parallel num_gangs(32) copyin(num_gangs)
    {
        num_gangs = __pgi_acc_get_num_gangs(); 
        sum = num_gangs;
        #pragma acc loop gang reduction(+:sum)
        for(int i=0 ; i<1024 ; i++){
            sum += 1;
        }
    }

    if(sum != (32 + 1024)){
        err = 1;
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