#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

int main()
{
    int gangs = 128;
    int var = 0;

    #pragma acc parallel num_gangs(gangs) copy(var)
    {
        if (acc_on_device(acc_device_not_host)) {
            int num = acc_get_num_gangs(acc_async_noval);
            if (__pgi_gangidx() == 0) var = num;
        }
        else {
            var = 1;
        }
    }

    // Verification
    if (var != gangs) {
        printf("Test failed! Expected gangs: %d, got: %d \n", gangs, var);
        return EXIT_FAILURE;
    }
    else {
        printf("Test success! Expected gangs: %d, got: %d \n", gangs, var);
    }

    return EXIT_SUCCESS;
}