#include <openacc.h>
#include <stdio.h>

void do_work()
{
    /* Simulated workload */
    int i, j;
    long int sum = 0;
    for (i=0; i<50000000; i++)
        sum = sum + i;
}

int main(int argc, char** argv)
{
    /* Launch do_work on the async queue with id 1 */
    #pragma acc parallel async(1)
    do_work();

    /* Launch do_work on the async queue with id 2 */
    #pragma acc parallel async(2)
    do_work();

    /* Wait for the first async task to finish */
    acc_wait_async(1, 1);

    printf("First async task is finished, waiting for the second one\n");

    /* Wait for the second async task to finish */
    acc_wait_async(2, 2);

    printf("All async tasks are finished!\n");

    return 0;
}