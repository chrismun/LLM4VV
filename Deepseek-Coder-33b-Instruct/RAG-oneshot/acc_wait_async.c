#include <stdio.h>
#include <openacc.h>

int main() {
    int async_arg1 = acc_async_sync;
    int async_arg2 = acc_async_sync;

    #pragma acc parallel async(async_arg1)
    {
        printf("First operation\n");
    }

    #pragma acc parallel async(async_arg2)
    {
        printf("Second operation\n");
    }

    acc_wait_async(async_arg1, async_arg2);

    printf("Both operations are done\n");

    return 0;
}