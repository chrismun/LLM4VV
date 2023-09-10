#include "acc_testsuite.h"
    #include <stdlib.h> //for malloc, rand
    #include <openacc.h> //for acc_malloc, acc_map_data, acc_unmap_data

    #ifndef T1
    /*T1:acc map data,V:2.0-2.7*/
    int test1(){
        int err = 0;
        srand(SEED);
        size_t bytes = 10*sizeof(float);
        float* h_data = (float*)malloc(bytes);
        float* d_data = (float*)acc_malloc(bytes);

        acc_map_data(h_data, d_data, bytes);
     
        /* Check if data_arg is mapped properly */
        if( acc_is_present(h_data, bytes) != 1 ){
            err = 1;
        }
        
        /* Clean up */
        acc_unmap_data(h_data);
        acc_free(d_data);
        free(h_data);

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