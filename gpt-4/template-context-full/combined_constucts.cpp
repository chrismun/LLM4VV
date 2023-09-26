#include "acc_testsuite.h"
#ifndef T1
/*T1:combined constructs, V:2.0-2.7 */
int test1(){
    int err = 0;
    const int array_size = 1000;
    float * a = (float*)malloc(sizeof(float)*array_size);

    srand(SEED);
    for (int i = 0; i < array_size; ++i) {
        a[i] = rand() % 100;
    }

    float b[array_size];
    #pragma acc parallel loop copy(a[0:array_size], b[0:array_size])
    for (int i = 0; i < 1000; ++i) {
        b[i] = a[i] * 2.0f;
    }

    for(int i = 0; i < array_size; ++i){
        if(fabs(output[i] - a[i] * 2.0f) > PRECISION) {
            err = 1;
            break;
        }
    }

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