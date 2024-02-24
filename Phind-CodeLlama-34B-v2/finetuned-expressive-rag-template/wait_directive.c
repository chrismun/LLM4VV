#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int err = 0;
    int *a, *b, *c;
    int i;

    a = (int *)malloc(10 * sizeof(int));
    b = (int *)malloc(10 * sizeof(int));
    c = (int *)malloc(10 * sizeof(int));

    for (i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    #pragma acc data copyin(a[0:10], b[0:10]) copyout(c[0:10])
    {
        #pragma acc kernels async(1)
        {
            for (i = 0; i < 10; i++) {
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc wait(1)

        for (i = 0; i < 10; i++) {
            if (c[i] != a[i] + b[i]) {
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}