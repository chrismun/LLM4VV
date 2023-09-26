#include "acc_testsuite.h"
#ifndef T1
/*T1:variable implicit data attributes,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const unsigned int N = 1024;
    int *a = (int *)malloc(sizeof(int) * N);
    int *b = (int *)malloc(sizeof(int) * N);

    // Initialize the arrays
    for(int i=0; i<N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc parallel copy(a[0:N], b[0:N])
    {
        if (!acc_is_present(a, (size_t) N * sizeof(int)) && !acc_is_present(b, (size_t) N * sizeof(int))){
            err = 1;
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