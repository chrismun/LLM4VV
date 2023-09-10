#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int num_gangs = 128;
    int a[num_gangs];
    int b[num_gangs];

    // Initialize array b with random values
    for (int i = 0; i < num_gangs; ++i) {
        b[i] = rand();
    }

    #pragma acc parallel num_gangs(num_gangs) copyin(b[0:num_gangs]) copy(a[0:num_gangs])
    {
        int idx = __pgi_gangidx();
        int private_var = b[idx]; // private variable, each gang will have its own copy
        a[idx] = private_var;
    }

    // Check if values of array a is as expected (equal to the corresponding elements in array b)
    // As each gang should have its own private copy of variable private_var,
    // the changes made by one gang should not affect the others, and the assignment to a[idx] should be correct.
    for (int i = 0; i < num_gangs; ++i) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
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