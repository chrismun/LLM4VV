#include "acc_testsuite.h"

int acc_get_default_async(void) {
    int err = 0;
    srand(SEED);

    // Get the current thread's asynchronous queue
    int async_queue = acc_get_async_queue();

    // If the queue is not the default queue, return an error
    if (async_queue != acc_async_noval) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Call the acc_get_default_async function and check the result
    failed = acc_get_default_async();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}