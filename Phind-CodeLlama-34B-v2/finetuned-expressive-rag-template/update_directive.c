#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 10

int main(){
    int a[NUM], b[NUM], i;
    int err = 0;

    for(i = 0; i < NUM; i++){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:NUM]) create(b[0:NUM])

    #pragma acc parallel present(a[0:NUM], b[0:NUM])
    {
        #pragma acc loop
        for(i = 0; i < NUM; i++){
            b[i] = a[i] * 2;
        }
    }

    #pragma acc update self(b[0:NUM])

    for(i = 0; i < NUM; i++){
        if(b[i] != a[i] * 2){
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:NUM], b[0:NUM])

    return err;
}