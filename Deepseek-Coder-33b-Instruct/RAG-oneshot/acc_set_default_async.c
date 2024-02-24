#include <stdio.h>
#include <openacc.h>

int main() {
    int default_async_queue = acc_get_default_async();
    printf("Default async queue: %d\n", default_async_queue);

    acc_set_default_async(1); // Set the default async queue to 1

    int new_default_async_queue = acc_get_default_async();
    printf("New default async queue: %d\n", new_default_async_queue);

    if (new_default_async_queue == 1) {
        printf("Default async queue set correctly.\n");
    } else {
        printf("Default async queue not set correctly.\n");
    }

    return 0;
}