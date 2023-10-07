#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_SIZE 1000
#define NUM_TEST_CALLS 5
#define SEED 12345

void initialize_array(float *data, int size) {
    for(int i = 0; i < size; i++) {
        data[i] = (float)i;
    }
}

int test1() {
    int err = 0;
    float *data = (float*)malloc(ARRAY_SIZE * sizeof(float));

    initialize_array(data, ARRAY_SIZE);

    #pragma acc parallel loop copy(data[0:ARRAY_SIZE])
    for(int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = data[i] + 1.0f;
    }

    for(int i = 0; i < ARRAY_SIZE; i++) {
        if(data[i] != (float)(i) + 1.0f) {
            err = 1;
            break;
        }
    }

    free(data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
  
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        printf("OpenACC test passed!\n");
    } else {
        printf("OpenACC test failed!\n");
    }

    return failcode;
}