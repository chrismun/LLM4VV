#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 100
#define SEED 123
#define NUM_TEST_CALLS 5

bool test(){

    // Initialize seed for random number
    srand(SEED);
    
    // Initialize device memory
    int* dev_mem = (int*)acc_malloc(SIZE * sizeof(int));

    // Initialize host pointers
    int* h_pointer = (int*)malloc(SIZE * sizeof(int));
    int* h_temp_pointer;
    
    for(int i = 0; i < SIZE; i++){
        h_pointer[i] = rand()%1000; // Random numbers
    }

    acc_memcpy_to_device(dev_mem, h_pointer, SIZE * sizeof(int));
    
    // Attach pointer to device
    acc_attach((void**)&dev_mem);

    // Copy value from device to host
    acc_memcpy_from_device(h_temp_pointer, dev_mem, SIZE * sizeof(int));
    
    // Detach pointer from device
    acc_detach((void**)&dev_mem);
    
    // Compare the objects
    for(int i = 0; i < SIZE; i++){
        if(h_pointer[i] != h_temp_pointer[i]){
            free(h_pointer);
            return false;
        }
    }
    free(h_pointer);
    return true;
}

int main(){
    bool pass = true;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        pass = pass && test();
        if (!pass) {
            printf("OpenACC acc_attach/acc_detach test failed\n");
            return 1;
        }
    }
    if (pass) {
        printf("OpenACC acc_attach/acc_detach test passed\n");
        return 0;
    }
}