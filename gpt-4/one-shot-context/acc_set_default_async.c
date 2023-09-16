#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

#define ASYNC_QUEUE 5

void async_test()
{
    // Set the default asynchronous queue.
    acc_set_default_async(ASYNC_QUEUE);

    // Get the default asynchronous queue.
    int actual_queue = acc_get_default_async();

    if (actual_queue != ASYNC_QUEUE) {
        printf("Test failed: Expected default async queue to be %d, but got %d\n", ASYNC_QUEUE, actual_queue);
        exit(EXIT_FAILURE);
    }
    
    // Reset the default async.
    acc_set_default_async(acc_async_default);
}

int main()
{
    async_test();
    printf("Test passed: acc_set_default_async works correctly\n");

    return 0;
}