#include "acc_testsuite.h"

#ifndef T1
#define LOOP_SIZE 1000
#define THRESHOLD 500

/*T1:kernels construct self clause,V:2.0-2.7*/
int test1() {
    int err = 0;
    int a[LOOP_SIZE];  
    
    // Initialize array on host
    for (int i = 0; i < LOOP_SIZE; ++i)
        a[i] = i;
    
    // Use OpenACC kernels with self clause
    #pragma acc kernels copy(a[:LOOP_SIZE]) if(LOOP_SIZE > THRESHOLD) self(LOOP_SIZE < THRESHOLD)
    {
        for(int i = 0; i < LOOP_SIZE; ++i)
            a[i] += 1;
    }
    
    // check results on host
    for(int i = 0; i < LOOP_SIZE; ++i)
        if (a[i] != i + 1)
            err = 1;
    
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