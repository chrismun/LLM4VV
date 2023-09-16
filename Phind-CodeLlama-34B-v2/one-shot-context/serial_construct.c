#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 1024

int validate_serial_construct(){
    int *a, *b;
    int i;
    int fail = 0;

    a = (int *)malloc(NUM * sizeof(int));
    b = (int *)malloc(NUM * sizeof(int));

    for(i = 0; i < NUM; i++){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:NUM]) copyout(b[0:NUM])
    {
        #pragma acc serial
        {
            #pragma acc loop
            for(i = 0; i < NUM; i++){
                b[i] = a[i] * 2;
            }
        }
    }

    for(i = 0; i < NUM; i++){
        if(b[i] != a[i] * 2){
            fail = 1;
            break;
        }
    }

    free(a);
    free(b);

    return fail;
}

int main(){
    int fail = 0;

    fail = validate_serial_construct();

    if(fail){
        printf("Validation failed.\n");
    } else {
        printf("Validation passed.\n");
    }

    return 0;
}