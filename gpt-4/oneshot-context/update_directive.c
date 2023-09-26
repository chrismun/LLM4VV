#include <stdio.h>
#include <openacc.h>

int main(){
    int n = 1000;
    int *device_array = NULL, *host_array = NULL;

    host_array = (int*) malloc(n*sizeof(int)); 
    for(int i=0; i<n; i++){
        host_array[i] = i;
    }

    acc_init(acc_device_default);

    device_array = (int*) acc_malloc(n*sizeof(int));

    #pragma acc enter data create(device_array[:n])

    // copying from host to device
    #pragma acc update device(device_array[:n])
    for(int i=0; i<n; i++){
        device_array[i] = host_array[i];
    }

    // copying data from device to host
    for(int i=0; i<n; i++){
        host_array[i] = 0;
    }
    #pragma acc update self(host_array[:n])
    for(int i=0; i<n; i++){
        host_array[i] = device_array[i];
    }

    int err = 0;
    for(int i=0; i<n; i++){
        if(host_array[i] != i){
            printf("Mismatch at position %d: %d != %d\n", i, host_array[i], i);
            err = 1;
        }
    }

    if (!err){
        printf("OpenACC update directive works correctly.\n");
    }

    acc_free(device_array);
    free(host_array);

    return 0;