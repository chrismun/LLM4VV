#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

int main() {
    int async_val = acc_get_default_async();
    printf("Default async value: %d\n", async_val);

    // Set the default async value to a non-default value
    acc_set_default_async(1);
    async_val = acc_get_default_async();
    printf("New default async value: %d\n", async_val);

    // Reset the default async value to the default value
    acc_set_default_async(0);
    async_val = acc_get_default_async();
    printf("Default async value: %d\n", async_val);

    return 0;
}