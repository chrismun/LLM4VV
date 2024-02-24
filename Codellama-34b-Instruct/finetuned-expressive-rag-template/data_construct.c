#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 100

int main(){
    int* a = (int*)malloc(NUM * sizeof(int));
    int* b = (int*)malloc(NUM * sizeof(int));

    for(int i = 0; i < NUM; i++){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copy(a[0:NUM]) copyout(b[0:NUM])
    {
        #pragma acc parallel loop
        for(int i = 0; i < NUM; i++){
            b[i] = a[i] * 2;
        }
    }

    int errors = 0;
    for(int i = 0; i < NUM; i++){
        if(b[i] != a[i] * 2){
            errors++;
            printf("Error at %d: expected %d, got %d\n", i, a[i] * 2, b[i]);
        }
    }

    free(a);
    free(b);

    if(errors != 0){
        return 1;
    }
    else{
        return 0;
    }
}