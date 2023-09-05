#include <openacc.h>

void acc_set_default_async(int async_arg) {
    acc_async_var_t async_var;
    int async_arg_val;

    // Check if the async_arg is a valid async-argument value
    if (async_arg < 0 || async_arg > ACC_ASYNC_MAX) {
        acc_error_invalid_async(async_arg);
        return;
    }

    // Set the default asynchronous activity queue to the specified queue
    async_var = acc_async_var_create(async_arg);
    async_arg_val = acc_async_var_get(async_var);
    acc_set_default_async_var(async_arg_val);
}