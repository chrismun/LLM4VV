#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    float a[N][N], b[N][N], r[N][N] = {0.0};

    // Initialize matrices a and b
    for(int i = 0 ; i < N ; ++i){
        for(int j = 0 ; j < N ; ++j){
            a[i][j] = (float)i;
            b[i][j] = (float)j;
        }
    }

    #pragma acc data copyin(a, b) copyout(r)
    {
    #pragma acc kernels
    {
        #pragma acc loop collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for(int k = 0; k < N; k++)
                    r[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    }

    //Print results (example)
    printf("r[0][0]=%f\n", r[0][0]);
    printf("r[N-1][N-1]=%f\n", r[N-1][N-1]);

    return 0;
}