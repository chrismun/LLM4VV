#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define N 1024
#define PRECISION 0.00001

int main() {
    int err = 0;
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    for (int i = 0; i < N; i++) {
        a[i] = i / 10.0;
        b[i] = 0;
    }

    #pragma acc data copyout(b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            err++;
        }
    }

    if (err > 0) {
        printf("Error: %d\n", err);
    } else {
        printf("Success\n");
    }

    free(a);
    free(b);

    return 0;
}