#include <stdio.h>
#include <openacc.h>

int main()
{
    acc_device_t initial_device_type, host_device_type;

    initial_device_type = acc_get_device_type();
    if (initial_device_type != acc_device_none)
    {
        printf("error: initially, expected acc_device_none but got %d\n", initial_device_type);
        return 1;
    }

    acc_set_device_type(acc_device_host);
    host_device_type = acc_get_device_type();
    if (host_device_type != acc_device_host)
    {
        printf("error: after setting device type to acc_device_host, expected acc_device_host but got %d\n", host_device_type);
        return 1;
    }

    printf("All tests passed\n");
    return 0;
}