internal control variables have been modified correctly.

Here's an example code that tests the set directive with the default_async and device_num clauses:

#ifdef _OPENACC
#include <openacc.h>
#endif

#include <stdio.h>

int main() {
    int err = 0;
    int default_async_val = 2;
    int device_num_val = 1;

    #pragma acc set default_async(default_async_val) device_num(device_num_val)

    #ifdef _OPENACC
    int acc_default_async_var = acc_get_default_async();
    int acc_current_device_num_var = acc_get_device_num();
    #else
    int acc_default_async_var = 0;
    int acc_current_device_num_var = 0;
    #endif

    if (acc_default_async_var != default_async_val) {
        printf("Error: acc_default_async_var = %d, expected %d\n", acc_default_async_var, default_async_val);
        err = 1;
    }

    if (acc_current_device_num_var != device_num_val) {
        printf("Error: acc_current_device_num_var = %d, expected %d\n", acc_current_device_num_var, device_num_val);
        err = 1;
    }

    if (err == 0) {
        printf("Compiler implementation of set directive is correct.\n");
    }

    return err;
}