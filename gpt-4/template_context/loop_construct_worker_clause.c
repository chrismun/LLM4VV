#include "acc_testsuite.h"

#define vector_length 1000 //choose a size suitable for your testing environment

int test1() {
    int err = 0;
    int* simple_test_vector = (int*)malloc(vector_length*sizeof(int));
    
    for(int i=0; i<vector_length; i++)
        simple_test_vector[i] = -1;

    #pragma acc parallel num_workers(4)
    {
        #pragma acc loop worker
        for(int i=0; i<vector_length; i++)
            simple_test_vector[i] = i;
    }

    for(int i=0; i<vector_length; i++) {
        if(simple_test_vector[i] != i) {
            err = 1;
            break;
        }
    }

    free(simple_test_vector);
    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}