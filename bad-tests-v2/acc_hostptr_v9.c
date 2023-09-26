#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024
#define PRECISION 0.0001

int main(){
    int i;
    real_t *a, *b, *c;
    real_t *d_a, *d_b;

    a = (real_t *)malloc(N * sizeof(real_t));
    b = (real_t *)malloc(N * sizeof(real_t));
    c = (real_t *)malloc(N * sizeof(real_t));

    for(i = 0; i < N; i++){
        a[i] = i * 1.0;
        b[i] = 0.0;
        c[i] = 0.0;
    }

    d_a = acc_copyin(a, N * sizeof(real_t));
    d_b = acc_copyin(b, N * sizeof(real_t));

    #pragma acc kernels present(d_a[0:N], d_b[0:N])
    {
        #pragma acc loop
        for(i = 0; i < N; i++){
            d_b[i] = d_a[i] * 2.0;
        }
    }

    acc_memcpy_from_device(c, d_b, N * sizeof(real_t));

    for(i = 0; i < N; i++){
        if(fabs(c[i] - (i * 1.0 * 2.0)) > PRECISION){
            printf("Test failed: c[%d] = %f, expected %f\n", i, c[i], (i * 1.0 * 2.0));
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}