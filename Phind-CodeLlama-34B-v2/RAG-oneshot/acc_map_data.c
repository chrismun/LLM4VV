#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define SEED 123

int validate_acc_map_data(){
    int i;
    int err = 0;
    unsigned int *h_data = (unsigned int *) malloc(NUM_ELEMENTS * sizeof(unsigned int));
    unsigned int *d_data = (unsigned int *) acc_malloc(NUM_ELEMENTS * sizeof(unsigned int));

    srand(SEED);
    for(i = 0; i < NUM_ELEMENTS; i++){
        h_data[i] = rand() % 100;
    }

    acc_map_data(h_data, d_data, NUM_ELEMENTS * sizeof(unsigned int));

    #pragma acc parallel present(h_data[0:NUM_ELEMENTS])
    {
        int idx = acc_thread_id();
        h_data[idx] += 1;
    }

    acc_unmap_data(h_data);

    for(i = 0; i < NUM_ELEMENTS; i++){
        if(h_data[i] != (rand() % 100 + 1)){
            err++;
            break;
        }
    }

    free(h_data);
    acc_free(d_data);

    return err;
}

int main(){
    int errors = validate_acc_map_data();
    if(errors != 0){
        printf("Validation failed with %d errors\n", errors);
        return 1;
    }
    printf("Validation passed\n");
    return 0;
}