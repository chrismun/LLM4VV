#include "openacc.h"
#include<stdbool.h>
#include<stdio.h>

// function to check if the memory is "live"
bool is_live(void *ptr)
{
    return acc_is_present(ptr, sizeof(ptr)) == 1;
}

int main() {
    int data = 123;   // Data that would be detached
    printf("is data live | before data creation: %d\n", is_live(&data));

    // data creation
    #pragma acc data create(data)
    {
        printf("is data live | after  data creation: %d\n", is_live(&data));
    }
    // Data is detached so, it should be "false"
    printf("is data live | after  call to data region: %d\n", is_live(&data));

    // data creation
    #pragma acc data create(data)
    {
        printf("is data live | after  data creation: %d\n", is_live(&data));
        #pragma acc exit data detach(data) // Detaching the data 
    }
    // Data is detached so, it should be "false"
    printf("is data live | after  call to exit data with detach: %d\n", is_live(&data));

    return 0;
}