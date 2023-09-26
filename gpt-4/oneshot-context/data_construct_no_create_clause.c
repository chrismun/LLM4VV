#include "stdlib.h"
#include "stdio.h"
#include "openacc.h"

int main(){

    int err = 0;
    int n = 100000;
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (float)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) no_create(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != 0.0){
            err = 1;
            printf("No_Create clause failed. Array b was updated! \n");
            break;
        }
    }

    free(a);
    free(b);

    return err;
}