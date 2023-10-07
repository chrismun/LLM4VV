#include <stdio.h>
#include <openacc.h>

void check_on_device() {
    int is_on_host = acc_on_device(acc_device_host);
    int is_not_on_host = acc_on_device(acc_device_not_host);
    int is_on_gpu = acc_on_device(acc_device_nvidia);

    printf("Is on host: %d\n", is_on_host);
    printf("Is not on host: %d\n", is_not_on_host);
    printf("Is on GPU: %d\n", is_on_gpu);
}

int main() {
    printf("Checking outside of parallel region:\n");
    check_on_device();

    printf("Checking inside of parallel region:\n");
    #pragma acc parallel
    {
        check_on_device();
    }

    return 0;
}