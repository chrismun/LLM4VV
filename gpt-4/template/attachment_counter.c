#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void check_acc(); 

int main(){
    const int N = 100;
    int i, fail = 0;
    int *a = (int*) malloc(sizeof(int)*N);
    int *b = (int*) malloc(sizeof(int)*N);
    int *c = (int*) malloc(sizeof(int)*N);

    // Initialize data
    for(i=0; i<N; i++){
        a[i] = 1;
        b[i] = 2;
    }

    #pragma acc parallel loop copyin(a[0:N], b[0:N]) copyout(c[0:N])
    for(i=0; i<N; i++){
        c[i] = a[i] + b[i];
    }

    // Check result  
    for(i=0; i<N; i++){
        if(c[i] != 3){
            printf("Error: value of c[%d] = %d instead of 3\n", i, c[i]);
            fail = 1;
        } 
    }

    // Free memory
    free(a);
    free(b);
    free(c);

    if(fail != 0){
        printf("Test failed\n");
        return 1;
    } else {
        printf("OpenACC implementation works correctly\n");
        return 0;
    }
    check_acc();        
}

void check_acc(){
    int acc_on_device = acc_on_device( acc_device_not_host );
    printf("ACC is on device: %s\n", acc_on_device ? "true" : "false");
}