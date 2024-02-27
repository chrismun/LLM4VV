#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:serial construct, num_gangs clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(2023);  // Define a seed for reproducibility

    // The num_gangs clause is not applicable directly to the serial construct.
    // Thus, we'll demonstrate a basic usage of the serial construct here,
    // but there will not be a direct test of num_gangs as it doesn't apply.
    int testData = rand() % 100;  // Generate random test data.
    int result = 0;

    // Serial execution region. In practice, num_gangs is not used with serial.
    #pragma acc serial copyin(testData) copy(result)
    {
        result = testData + 1;  // Simple operation to verify serial execution.
    }

    // Check if the operation was successful.
    if (result != testData + 1) {
        err++;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) {  // Only one test call because the check is deterministic.
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}