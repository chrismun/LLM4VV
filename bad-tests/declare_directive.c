#include "acc_testsuite.h"

/* Test declaration directive in OpenACC */
int test_declare_directive(){
    int err = 0; // Error tracking variable
    int size = 100; // Size of data array
    srand(SEED); // Random seed for initialization

    // Declare data variables
    float* host_data = (float*)malloc(size*sizeof(float));
    float* res_data = (float*)malloc(size*sizeof(float));
    #pragma acc declare create(host_data[0:size]) // Declare OpenACC directive

    // Initialize host data
    for (int i = 0; i < size; i++){
        host_data[i] = (float) rand() / RAND_MAX;
        res_data[i] = host_data[i];
    }

    // Compute on OpenACC device
    #pragma acc parallel loop present(host_data[0:size])
    for (int i = 0; i < size; i++){
        host_data[i] = host_data[i] * host_data[i];
    }

    // Retrieve result back from OpenACC device
    #pragma acc update host(host_data[0:size])

    // Verify result
    for (int i = 0; i < size; i++){
        if(fabsf(host_data[i] - res_data[i] * res_data[i]) > PRECISION){
            err = 1;
        }
    }

    // Free memory
    free(host_data);
    free(res_data);

    return err;
}

int main(){
    int error_count = 0;

    // Test declare directive
    for (int x = 0; x < NUM_TEST_CALLS; x++){
        error_count += test_declare_directive();
    }
   
    return error_count;
}