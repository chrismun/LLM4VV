#include <openacc.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int* a = (int*)malloc(sizeof(int));
    int* b = (int*)malloc(sizeof(int));

    *a = 0;
    *b = 0;

    #pragma acc data copyout(a[0:1], b[0:1])
    {
        // we set the default async queue to 1
        acc_set_default_async(1);

        #pragma acc parallel async(0)
        {
            sleep(2); // delay function
            *a = 1;
        }

        #pragma acc parallel async // it should go to async queue 1
        {
            *b = 1;
        }

        acc_wait_all(); // wait until all operations are done
    }

    // if 'acc_set_default_async' is implemented correctly, second kernel should be executed before the first one.
    if(*a != 1 || *b != 1){
        printf("acc_set_default_async implementation is incorrect\n");

        free(a);
        free(b);

        return 1;
    }

    printf("acc_set_default_async implementation is correct\n");

    free(a);
    free(b);

    return 0;
}