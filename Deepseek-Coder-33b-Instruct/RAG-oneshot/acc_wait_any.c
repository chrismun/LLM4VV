#include <stdio.h>
#include <openacc.h>

int main() {
    int count = 10;
    int wait_arg[10];
    int dev_num = 0;

    // Initialize the async queues
    for (int i = 0; i < count; i++) {
        wait_arg[i] = acc_async_sync;
    }

    // Wait for any of the async queues to complete
    int index = acc_wait_any(count, wait_arg);

    // Check if any of the async queues completed
    if (index != -1) {
        printf("Async queue %d completed\n", index);
    } else {
        printf("No async queue completed\n");
    }

    return 0;
}