#include "acc_testsuite.h"

#ifndef T1
/*T1:kernels construct firstprivate clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int length = 1024;
    int* a = (int*)malloc(sizeof(int)*length);
    int* b = (int*)malloc(sizeof(int)*length);
    int* c = (int*)malloc(sizeof(int)*length);

    for(int i=0; i<length; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    int scalar = rand() % 100;

    #pragma acc kernels copyin(a[0:length], b[0:length]), copyout(c[0:length]), firstprivate(scalar)
    for(int i=0; i<length; i++) {
        c[i] = a[i] + scalar * b[i];
    }

    #pragma acc host_data use_device(a, b, c)
    {
        for(int i=0; i<length; i++) {
            if(c[i] != (a[i] + scalar * b[i])) {
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);
    free(c);

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