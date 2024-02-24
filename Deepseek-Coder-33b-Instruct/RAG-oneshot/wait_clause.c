#include <stdio.h>
#include <openacc.h>

int main() {
    int i;

    // Create a parallel region
    #pragma acc parallel
    {
        int thread_id = acc_get_device_num(acc_device_self);
        printf("Thread %d is running\n", thread_id);
    }

    // Wait for all threads in the region to complete
    #pragma acc wait

    printf("All threads have completed\n");

    return 0;
}