#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        int i;
        #pragma acc loop independent
        for (i = 0; i < N; i++) {
            if (i % 2 == 0) {
                c[i] = a[i] + b[i];
            } else {
                c[i] = a[i] - b[i];
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (i % 2 == 0 && c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        } else if (i % 2 != 0 && c[i] != a[i] - b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Success\n");
    return 0;
}