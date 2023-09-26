#include "acc_testsuite.h"

#ifndef T1
/*T1:parallel construct wait clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 1024;
    int *a = (int*)malloc(array_size * sizeof(int));
    int *b = (int*)malloc(array_size * sizeof(int));
   
    // Initialize a and b arrays with random data
    for(int i = 0; i < array_size; i++) {
        a[i] = rand() % 1024;
        b[i] = 0;
    }
    
    #pragma acc data copyin(a[0:array_size]) copyout(b[0:array_size])
    {
        #pragma acc parallel async
        {
            #pragma acc loop
            for(int i = 0; i < array_size; i++) {
                b[i] = a[i] * 2;
            }
        }

        #pragma acc wait

        for(int i = 0; i < array_size; i++) {
            if(b[i] != a[i] * 2) {
                err = 1;
                break;
            }
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