#include <stdlib.h>
#include <stdio.h>

#pragma acc routine seq
void print_device_resident(int *a) {
    printf("Device resident variable: %d\n", *a);
}

int main() {
    int *a = (int*)malloc(sizeof(int));
    *a = 10;

    #pragma acc data device_resident(a)
    {
        #pragma acc host_data use_device(a)
        {
            print_device_resident(a);
        }
    }

    free(a);

    return 0;
}