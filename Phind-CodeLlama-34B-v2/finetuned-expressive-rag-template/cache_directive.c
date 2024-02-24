#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main(){
    int a[N], b[N], c[N];
    int i;
    int err = 0;

    for(i = 0; i < N; i++){
        a[i] = i;
        b[i] = i * 2;
    }

    #pragma acc data copy(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < N; i++){
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc cache(a[0:N/2], b[0:N/2])
        {
            #pragma acc kernels
            {
                #pragma acc loop
                for(i = 0; i < N/2; i++){
                    c[i] = a[i] - b[i];
                }
            }
        }
    }

    for(i = 0; i < N/2; i++){
        if(c[i] != a[i] - b[i]){
            err = 1;
            break;
        }
    }

    for(i = N/2; i < N; i++){
        if(c[i] != a[i] + b[i]){
            err = 1;
            break;
        }
    }

    if(err){
        printf("Failed\n");
        return 1;
    }
    else{
        printf("Passed\n");
        return 0;
    }
}