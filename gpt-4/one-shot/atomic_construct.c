Testing the atomic operation:

#include "acc_testsuite.h"
#ifndef T1
//T1:atomic,default,V:1.0-2.7
void test1{
    int err = 0;
    int gangs = 900;
    int vectors = 32;
    int *num_ops = (int *)malloc(sizeof(int));
    
    *num_ops = 0;
    srand(SEED);

    #pragma acc data copy(num_ops[0:1])
    {
        #pragma acc parallel num_gangs(gangs) vector_length(vectors)
        {
            #pragma acc loop gang vector
            for (int x = 0; x < gangs*vectors; ++x){
                #pragma acc atomic update
                *num_ops += 1;
            }
        }
    }

    if (*num_ops != gangs*vectors){
        err = 1;
    }

    // Cleanup
    free(num_ops);

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