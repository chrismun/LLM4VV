#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_QUEUES 4
#define QUEUE_SIZE 10

int main() {
    int i, j, k;
    int async_queues[NUM_QUEUES];
    int async_handles[QUEUE_SIZE];
    int index;

    // Initialize async_queues
    for (i = 0; i < NUM_QUEUES; i++) {
        async_queues[i] = i;
    }

    // Launch async kernels
    for (i = 0; i < QUEUE_SIZE; i++) {
        async_handles[i] = acc_async_test_all();
    }

    // Wait for any queue to complete
    index = acc_wait_any(NUM_QUEUES, async_queues);

    if (index >= 0 && index < NUM_QUEUES) {
        printf("acc_wait_any successfully waited for queue %d\n", index);
    } else {
        printf("acc_wait_any failed\n");
    }

    return 0;
}