#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:parallel construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    int num_workers = 4; // Specify the number of workers

    // Create a parallel region with the specified number of workers
    #pragma acc parallel num_workers(num_workers)
    {
        int thread_id = acc_get_device_num(acc_device_not_host);
        printf("Hello from worker %d\n", thread_id);
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}