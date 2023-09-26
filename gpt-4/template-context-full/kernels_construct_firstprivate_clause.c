#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:kernels construct firstprivate clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int*)malloc(10*sizeof(int));
    int *b = (int*)malloc(10*sizeof(int));
    
    #pragma acc data create(a[0:10]) copy(b[0:10])
    {
        #pragma acc update device(a[0:10])
        
        for(int i=0; i<10; i++)
        {
            a[i]=rand()%100;
        }

        int preview_a = a[5];

        #pragma acc kernels firstprivate(preview_a)
        {
            for(int i=0; i<10; i++)
            {
                b[i] = a[i] + preview_a;
            }
        }

        #pragma acc update host(b[0:10])

        for(int i=0; i<10; i++)
        {
            if(b[i] != a[i] + preview_a){
                err = 1;
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