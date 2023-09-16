#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>

#ifndef T1
#define T1

//T1:acc set device type,V:2.7-3.3
int test_device_type_set()
{
    int err = 0;
    srand(SEED);
    const acc_device_t expected_device_type = acc_device_nvidia;  // change this as per the device availability

    acc_set_device_type(expected_device_type);
    acc_device_t actual_device_type = acc_get_device_type();  // Get the current device type

    if(actual_device_type != expected_device_type)
    {
        // If the set device type doesn't match the get device type, set err to 1
        err = 1;  
    }
    return err;
}

#endif

int main()
{
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        failed = failed + test_device_type_set();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}