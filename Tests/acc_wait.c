#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number of threads
    int num_threads = rand() % 10 + 1;

    // Create a barrier with the number of threads
    acc_barrier_t barrier;
    acc_barrier_init(&barrier, num_threads);

    // Create a thread that waits on the barrier
    pthread_t thread;
    pthread_create(&thread, NULL, wait_on_barrier, &barrier);

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    // Check if the barrier was correctly waited on
    if (barrier.num_waiting != num_threads) {
        err = 1;
    }

    return err;
}

void *wait_on_barrier(void *arg) {
    acc_barrier_t *barrier = (acc_barrier_t *)arg;
    acc_barrier_wait(barrier);
    return NULL;
}

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}