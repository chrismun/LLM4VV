#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int device_num = acc_get_device_num();
    printf("Current device number: %d\n", device_num);
    return 0;