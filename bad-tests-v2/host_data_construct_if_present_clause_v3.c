#include <stdlib.h>
#include <openacc.h>
#define SIZE 10
#define SEED 123
#define NUM_TEST_CALLS 5

int if_present_test(){
    int err = 0;
    srand(SEED);
    
    int *array = (int*)malloc(SIZE * sizeof(int));
    
    for (int i = 0; i < SIZE; i++){
        array[i] = rand() % 100;
    }

    #pragma acc data copy(array[0:SIZE])
    {
        #pragma acc host_data use_device(array)
        {
            #pragma acc parallel loop
            for (int i = 0; i < SIZE; i++){
                array[i] += 1;
            }
        }

        #pragma acc host_data if_present(array)
        {
            for (int i = 0; i < SIZE; i++){
                if (array[i] != i + 1){
                    err = 1;
                    break;
                }
            }
        }
    }

    free(array);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += if_present_test();
    }

    if (failed != 0){
        failcode = (1 << 0);
    }

    return failcode;
}