#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int i;
    real_t *a, *d_a;
    a = (real_t *)malloc(N * sizeof(real_t));

    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    #pragma acc enter data copyin(a[0:N])

    d_a = acc_deviceptr(a);

    #pragma acc exit data delete(a[0:N])

    if (d_a == NULL) {
        printf("Data is not present in the current device memory.\n");
    } else {
        printf("Device pointer: %p\n", d_a);
    }

    free(a);
    return 0;
}