#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#define N 100000000
#define TRIALS 10

int main(){
    double *a, *b;
    a = (double*)malloc(N*sizeof(double));
    b = (double*)malloc(N*sizeof(double));

    for(int i=0; i<N; i++){
        a[i] = i;
        b[i] = 0;
    }

    clock_t start, end;
    double cpu_time_used;

    // Test without async clause
    start = clock();
    for(int t=0; t<TRIALS; t++){
        #pragma acc data copy(a[0:N], b[0:N])
        {
            #pragma acc kernels
            {
                #pragma acc loop
                for(int i=0; i<N; i++){
                    b[i] = a[i];
                }
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken without async clause: %f\n", cpu_time_used);

    // Test with async clause
    start = clock();
    for(int t=0; t<TRIALS; t++){
        #pragma acc data copy(a[0:N], b[0:N])
        {
            #pragma acc kernels async
            {
                #pragma acc loop
                for(int i=0; i<N; i++){
                    b[i] = a[i];
                }
            }
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken with async clause: %f\n", cpu_time_used);

    free(a);
    free(b);

    return 0;
}