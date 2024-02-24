#include <stdio.h>
#include <openacc.h>

int main() {
    int a[100], b[100], c[100];
    int i;

    for (i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:100], b[0:100]) copyout(c[0:100])
    {
        #pragma acc parallel loop async(1)
        for (i = 0; i < 100; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc wait(1) async(2)
        for (i = 0; i < 100; i++) {
            c[i] = a[i] - b[i];
        }

        #pragma acc wait(2)
    }

    for (i = 0; i < 100; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}