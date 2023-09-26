#include "acc_testsuite.h"
#ifndef T1
/*T1:atomic construct,V:2.0-2.7*/
int test1() {
    int err = 0;
    unsigned int gangNum = 10;
    unsigned int workerNum = 10;
    unsigned int vectorNum = 10;
    unsigned int counter = 0;

    srand(SEED);

#pragma acc data copy(counter)
    {
#pragma acc parallel num_gangs(gangNum) num_workers(workerNum) vector_length(vectorNum)
        {
#pragma acc loop gang worker vector reduction(+:counter)
            for(int i = 0; i < gangNum * workerNum * vectorNum; ++i) {
#pragma acc atomic
                counter += 1;
            }
        }
    }

    // Should be equal to total count of parallel units
    if(counter != gangNum * workerNum * vectorNum) {
        err = 1;
    }

    return err;
}
#endif

int main() {
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