#include <stdio.h>
#include <openacc.h>

int main() {
    int async = acc_get_default_async(); // fetches default async queue
    if(async != acc_async_noval) { // Checks if default is not set to noval (-1)
        printf("Error: Default async queue should be acc_async_noval (-1) instead got %d.\n", async);
        return -1;
    }
    printf("OpenACC Compiler acc_get_default_async implementation is correct.\n");
    return 0;
}