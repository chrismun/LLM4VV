#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 16;
    int num_vectors = 10;
    int num_elements = vector_length * num_vectors;

    int* data = (int*)malloc(num_elements * sizeof(int));
    int* result = (int*)malloc(num_elements * sizeof(int));

    #pragma acc data copy(data[0:num_elements])
    {
        #pragma acc parallel loop vector_length(vector_length)
        for (int i = 0; i < num_vectors; i++) {
            for (int j = 0; j < vector_length; j++) {
                data[i * vector_length + j] = i * j;
            }
        }
    }

    #pragma acc data copy(result[0:num_elements])
    {
        #pragma acc parallel loop vector_length(vector_length)
        for (int i = 0; i < num_vectors; i++) {
            for (int j = 0; j < vector_length; j++) {
                result[i * vector_length + j] = data[i * vector_length + j];
            }
        }
    }

    for (int i = 0; i < num_elements; i++) {
        if (result[i] != data[i]) {
            err = 1;
            break;
        }
    }

    free(data);
    free(result);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}