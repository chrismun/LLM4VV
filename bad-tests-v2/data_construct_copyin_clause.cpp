#include "acc_testsuite.h"
#include <cmath>

#ifndef T1
/*T1:data construct copyin clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int* a = (int*)malloc(10 * sizeof(int));
    int* a_host = (int*)malloc(10 * sizeof(int));

    for(int i=0; i<10; i++){
        a_host[i] = rand() % 100; 
    }

    #pragma acc enter data copyin(a[0:10])
    
    // Copy a_host into a on the device
    #pragma acc parallel present(a[0:10])
    {
        #pragma acc loop
        for(int i=0; i<10; i++){
            a[i] = a_host[i];
        }
    }
    
    // Test the result off device
    for(int i=0; i<10; i++){
        if(a[i] != a_host[i]){
            err = 1;
        }
    }
    
    #pragma acc exit data delete(a[0:10])
    
    free(a_host);
    free(a);
    
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