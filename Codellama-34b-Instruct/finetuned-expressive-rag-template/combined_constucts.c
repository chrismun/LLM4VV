#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 1024

int main(){
    int *a, *b;
    int fail = 0;

    a = (int*)malloc(NUM * sizeof(int));
    b = (int*)malloc(NUM * sizeof(int));

    for(int i = 0; i < NUM; i++){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:NUM])
    #pragma acc enter data create(b[0:NUM])

    #pragma acc parallel loop present(a, b)
    for(int i = 0; i < NUM; i++){
        b[i] = a[i];
    }

    #pragma acc parallel loop present(a, b)
    for(int i = 0; i < NUM; i++){
        a[i] = b[i];
    }

    #pragma acc exit data copyout(a[0:NUM]) delete(b[0:NUM])

    for(int i = 0; i < NUM; i++){
        if(a[i] != i){
            fail = 1;
            break;
        }
    }

    free(a);
    free(b);

    return fail;
}