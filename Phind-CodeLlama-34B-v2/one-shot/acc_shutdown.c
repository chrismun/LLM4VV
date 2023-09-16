#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main(){
    int n = 1000;
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    acc_shutdown(acc_device_nvidia);

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            printf("Validation failed at index %d\n", x);
            return 1;
        }
    }

    printf("Validation passed\n");
    return 0;
}