#include <stdio.h>
#include <stdlib.h>
#include <OpenACC.h>

#define NUM_THREADS 256
#define NUM_ITERATIONS 1000

int validate_loop_variable_privacy() {
    int errors = 0;
    int *loop_variable = (int *) malloc(NUM_THREADS * sizeof(int));

    #pragma acc parallel num_gangs(1) num_workers(1) vector_length(NUM_THREADS)
    {
        int thread_id = acc_thread_id();
        loop_variable[thread_id] = 0;

        #pragma acc loop
        for (int i = 0; i < NUM_ITERATIONS; ++i) {
            loop_variable[thread_id] += 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (loop_variable[i] != NUM_ITERATIONS) {
            errors += 1;
        }
    }

    free(loop_variable);
    return errors;
}

int main() {
    int errors = validate_loop_variable_privacy();

    if (errors != 0) {
        printf("Validation failed with %d errors.\n", errors);
        return 1;
    } else {
        printf("Validation passed.\n");
        return 0;
    }
}