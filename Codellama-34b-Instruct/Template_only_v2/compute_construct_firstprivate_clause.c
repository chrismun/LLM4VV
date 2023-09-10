#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = rand();
    int b = rand();
    int c = rand();

    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        int firstprivate_a = a;
        int firstprivate_b = b;
        int firstprivate_c = c;

        #pragma acc loop gang
        for (int i = 0; i < 10; i++) {
            firstprivate_a += i;
            firstprivate_b += i;
            firstprivate_c += i;
        }

        #pragma acc loop vector
        for (int i = 0; i < 10; i++) {
            firstprivate_a += i;
            firstprivate_b += i;
            firstprivate_c += i;
        }
    }

    if (firstprivate_a != a + 10 || firstprivate_b != b + 10 || firstprivate_c != c + 10) {
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