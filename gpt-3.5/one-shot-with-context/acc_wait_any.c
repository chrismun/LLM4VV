#include <stdio.h>
#include <openacc.h>

int main() {
    const int num_queues = 3;
    acc_queue_t queues[num_queues];
    int index;

    // Create asynchronous queues
    for (int i = 0; i < num_queues; i++) {
        acc_create_queue(&queues[i]);
    }

    // Execute some asynchronous operations on the queues
    // ...

    // Wait for any of the queues to complete
    index = acc_wait_any(num_queues, queues);

    // Print the index of the completed queue
    printf("Queue %d completed first\n", index);

    // Destroy the queues
    for (int i = 0; i < num_queues; i++) {
        acc_destroy_queue(queues[i]);
    }

    return 0;