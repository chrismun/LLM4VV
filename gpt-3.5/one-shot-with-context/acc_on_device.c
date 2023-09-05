#include "acc_testsuite.h"

int main()
{
    int dev_type = acc_on_device(acc_device_gpu);
    
    if (dev_type)
    {
        printf("Running on GPU\n");
    }
    else
    {
        printf("Not running on GPU\n");
    }
    
    return 0;