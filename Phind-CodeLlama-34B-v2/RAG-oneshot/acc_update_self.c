#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define PRECISION 0.0001

int validate_acc_update_self(){
    int i;
    double *host_array, *device_array;
    host_array = (double *) malloc(NUM_ELEMENTS * sizeof(double));
    device_array = (double *) acc_malloc(NUM_ELEMENTS * sizeof(double));

    for(i = 0; i < NUM_ELEMENTS; i++){
        host_array[i] = i;
        device_array[i] = 0.0;
    }

    acc_memcpy_to(device_array, host_array, NUM_ELEMENTS * sizeof(double));

    for(i = 0; i < NUM_ELEMENTS; i++){
        device_array[i] += 1.0;
    }

    acc_update_self(device_array, NUM_ELEMENTS * sizeof(double));

    int error = 0;
    for(i = 0; i < NUM_ELEMENTS; i++){
        if(fabs(host_array[i] - (i + 1)) > PRECISION){
            error = 1;
            break;
        }
    }

    acc_free(device_array);
    free(host_array);

    return error;
}

int main(){
    int error = validate_acc_update_self();
    if(error != 0){
        printf("Validation failed.\n");
        return 1;
    }
    printf("Validation passed.\n");
    return 0;
}