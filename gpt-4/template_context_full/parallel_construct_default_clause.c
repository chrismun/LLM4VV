#include "acc_testsuite.h"
#include <stdlib.h>

/*T1:parallel construct default clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int a = 5;
    int b = 10;
    int c = 0;

    #pragma acc parallel default(none)
    {
        c = a + b;
    }

    // If 'a' and 'b' were not recognized within the parallel region due to the default(none) clause,
    // the addition operation won't perform correctly and 'c' will remain 0. Hence we use this fact to validate our test.

    if (c == 0){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    srand(time(0));

    failed = 0;
    for (int x = 0; x < 100; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + 1;
    }

    return failcode;
}