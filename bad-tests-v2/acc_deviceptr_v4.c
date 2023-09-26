#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 10;
    float *a;
    float *devptr;
    int i;

    a = (float *)malloc(n * sizeof(float));
    for (i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    devptr = (float *)acc_deviceptr(a);
    if (devptr == NULL) {
        printf("Device pointer is null\n");
    } else {
        printf("Device pointer: %p\n", devptr);
    }

    free(a);

    return 0;