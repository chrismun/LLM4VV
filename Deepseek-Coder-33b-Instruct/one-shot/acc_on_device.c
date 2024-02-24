#include <stdio.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Success: acc on device is working correctly.\n");
    return 0;
}