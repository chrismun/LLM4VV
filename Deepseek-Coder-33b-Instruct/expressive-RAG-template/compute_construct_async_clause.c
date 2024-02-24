#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:compute construct async clause,V:2.7-3.3
int test1(){
    int err = 0;

    #pragma acc data copy(err)
    {
        #pragma acc parallel async
        {
            // This task will be executed asynchronously
            printf("Async task\n");
        }

        #pragma acc parallel
        {
            // This task will be executed after the async task
            printf("Main task\n");
        }

        // Wait for all tasks to finish
        #pragma acc wait
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}