#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024

int test_cache_directive() {
    int err = 0;
    srand(time(NULL));

    int *input_array = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    int *output_array = (int *)malloc(NUM_ELEMENTS * sizeof(int));

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        input_array[i] = rand() % 100;
        output_array[i] = 0;
    }

    #pragma acc data copy(input_array[0:NUM_ELEMENTS], output_array[0:NUM_ELEMENTS])
    {
        #pragma acc kernels
        {
            #pragma acc cache(input_array[0:NUM_ELEMENTS])
            {
                #pragma acc loop
                for (int i = 0; i < NUM_ELEMENTS; i++) {
                    output_array[i] = input_array[i];
                }
            }
        }
    }

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (input_array[i] != output_array[i]) {
            err = 1;
            break;
        }
    }

    free(input_array);
    free(output_array);

    return err;
}

int main() {
    int failed = 0;
    for (int x = 0; x < 10; ++x) {
        failed = failed + test_cache_directive();
    }
    if (failed != 0) {
        printf("Test failed\n");
        return 1;
    }
    printf("Test passed\n");
    return 0;
}