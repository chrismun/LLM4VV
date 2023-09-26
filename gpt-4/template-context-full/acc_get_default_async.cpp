#include "acc_testsuite.h"
#include "openacc.h"

#ifndef T1
/*T1:acc get default async,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);

    int default_async = acc_get_default_async();

    #pragma acc parallel vector_length(128) async
    {
    }

    #pragma acc wait

    if (default_async != acc_get_default_async()) {
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}