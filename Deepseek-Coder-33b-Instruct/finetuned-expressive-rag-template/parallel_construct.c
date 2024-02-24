#include <stdio.h>
#include <openacc.h>

int main() {
    int i;
    int err = 0;

    #pragma acc parallel
    {
        int thread_id = acc_get_device_num(acc_device_not_host);
        printf("Thread id: %d\n", thread_id);
    }

    return err;
}