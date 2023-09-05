#include <stdio.h>
#include <openacc.h>

int main() {
    int n = 1000;      
    float *restrict a = (float*) malloc(n * sizeof(float));
    float *restrict b = (float*) malloc(n * sizeof(float));
    float total = 0.0;
    
    for (int i = 0; i < n; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(total)
    {
        #pragma acc serial loop reduction(+:total)
        for (int i = 0; i < n; i++) {
            total += a[i] * b[i];
        }
    }
    
    printf("Total: %f\n", total);
    free(a);
    free(b);

    return 0;
}