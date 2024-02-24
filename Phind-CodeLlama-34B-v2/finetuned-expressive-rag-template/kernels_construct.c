#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 1000

int main(){
    int *a, *b, *c, i;
    a = (int*)malloc(NUM*sizeof(int));
    b = (int*)malloc(NUM*sizeof(int));
    c = (int*)malloc(NUM*sizeof(int));

    for(i=0; i<NUM; i++){
        a[i] = i;
        b[i] = i*2;
    }

    #pragma acc kernels
    {
        #pragma acc loop
        for(i=0; i<NUM; i++){
            c[i] = a[i] + b[i];
        }
    }

    for(i=0; i<NUM; i++){
        if(c[i] != a[i] + b[i]){
            printf("Test failed\n");
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}