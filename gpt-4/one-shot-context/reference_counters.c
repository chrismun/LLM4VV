#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

#define N 100000

// This function will test OpenACC compiler implementation
void test() {
    int *host_arr = (int*) malloc(N * sizeof(int));
    int *device_arr = (int*) malloc(N * sizeof(int));

    // Initialize host array inital values
    for(int i = 0; i < N; i++){
        host_arr[i] = i;
    }

    // Copy data from host to device
    #pragma acc enter data copyin(host_arr[0:N])

    // increment each array element by 1
    #pragma acc parallel loop present(host_arr)
    for(int i = 0; i < N; i++){
        host_arr[i] += 1;
    }
    
    // Copy data back to device array
    #pragma acc exit data copyout(host_arr[0:N]) 

    // Check each array value is incremented correctly
    for(int i = 0; i < N; i++){
        if(host_arr[i] != (i + 1)){
            printf("Test failed at index %d. Expected %d, got %d\n", i, i + 1, device_arr[i]);
            return;
        }
    }

    printf("Test passed. Confirming OpenACC compiler implementation for copyout.\n");
}

int main(){
    test();
    return 0;
}