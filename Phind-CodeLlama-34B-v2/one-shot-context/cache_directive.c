#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define N 1024
#define PRECISION 0.0001

int main(){
    int i;
    double a[N], b[N];

    for(i = 0; i < N; i++){
        a[i] = i * 1.0;
        b[i] = 0.0;
    }

    #pragma acc data copyin(a[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < N; i++){
                #pragma acc cache(a[i:1])
                {
                    b[i] = a[i];
                }
            }
        }
    }

    for(i = 0; i < N; i++){
        if(fabs(a[i] - b[i]) > PRECISION){
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}