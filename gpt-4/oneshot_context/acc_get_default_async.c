#include <stdio.h>
#include <openacc.h>

// function to set and get default async
void check_default_async() {
    int default_async;

    // Set default to async queue 1
    acc_set_default_async(1);
    
    // Get the default async
    default_async = acc_get_default_async();

    // Print the value
    printf("Default async value after setting: %d\n", default_async);

    // Set default back to ACC_ASYNC_SYNC (value = -1)
    acc_set_default_async(-1);

    // Get the default async
    default_async = acc_get_default_async();

    // Print the value
    printf("Default async value after resetting: %d\n", default_async);
}

int main() {

    // Call the function to set and get default async
    check_default_async();

    return 0;
}