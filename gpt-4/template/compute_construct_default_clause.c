#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1000

void fill_array(float *data){
    for (unsigned i = 0; i < SIZE; ++i)
        data[i] = (float)rand() / RAND_MAX;
}

float serial_sum(float *data){
    float val = 0;
    for (unsigned i = 0; i < SIZE; ++i)
        val += data[i];
    return val;
}

float parallel_sum(float *data){
    float val = 0;
    #pragma acc parallel loop reduction(+:val)
    for (unsigned i = 0; i < SIZE; ++i)
        val += data[i];
    return val;
}

int main(){
    float *data = (float*) malloc(sizeof(float) * SIZE);
    fill_array(data);

    // Calculate sum using serial sum function
    float serial_val = serial_sum(data);

    // Calculate sum using parallel sum function
    float parallel_val = parallel_sum(data);

    // Compare the results
    if(abs(serial_val - parallel_val) < 0.0001){
        printf("OpenACC implementation is correct.\n");
        return 0;
    }
    else{
        printf("OpenACC implementation is incorrect.\n");
        return 1;
    }

    free(data);
}