#include <stdlib.h>
#include <openacc.h>

int test1(){
    int err = 0;
    int num_gangs = 128;
    int num_vectors = 32;
    int* results = (int*)calloc(num_gangs * num_vectors, sizeof(int));

    // Execute a parallel section with a private 'thread_idx' variable for each thread
    #pragma acc parallel num_gangs(num_gangs) vector_length(num_vectors) copyout(results[0:num_gangs * num_vectors])
    {
        // Calculate a unique index for the current thread
        int thread_idx = acc_gangnum() * num_vectors + acc_vectornum();
        #pragma acc loop gang worker
        for (int i = 0; i < num_gangs * num_vectors; i++){
            // Set the thread's element in the 'results' array to its index
            #pragma acc loop seq
            for (int j = 0; j < num_vectors; ++j){
                if(i == thread_idx)
                    results[i] = thread_idx;
            }
        }
    }
    
    // Check that each thread wrote its index to the correct location
    for (int i = 0; i < num_gangs * num_vectors; ++i){
        if (results[i] != i){
            err = 1;
            break;
        }
    }

    free(results);
    return err;
}