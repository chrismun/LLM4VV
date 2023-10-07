#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:kernels construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int vector_length = 4;
    int num_vectors = 10;
    int num_elements = vector_length * num_vectors;
    int* data = (int*)malloc(num_elements * sizeof(int));

    #pragma acc kernels vector_length(vector_length)
    {
        for (int i = 0; i < num_vectors; i++) {
            for (int j = 0; j < vector_length; j++) {
                data[i * vector_length + j] = i * vector_length + j;
            }
        }
    }

    for (int i = 0; i < num_vectors; i++) {
        for (int j = 0; j < vector_length; j++) {
            if (data[i * vector_length + j] != i * vector_length + j) {
                err = 1;
                break;
            }
        }
    }

    free(data);

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