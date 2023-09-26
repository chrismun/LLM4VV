#include "acc_testsuite.h"

#ifndef T1
/*T1:acc map data,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    size_t len = 1024; //or any other size
    float *h_data = (float*) malloc(len * sizeof(float));
    float *d_data = acc_malloc(len * sizeof(float));

    if(h_data == NULL || d_data == NULL) {
        err = 1;
        return err; 
    }

    for(size_t i = 0; i < len; i++)
            h_data[i] = rand() / (float)RAND_MAX; 

    acc_map_data(h_data, d_data, len * sizeof(float));

    if(acc_is_present(h_data, len * sizeof(float)) == 0){
        err = 1;
    }

    acc_unmap_data(h_data);

    free(h_data);
    acc_free(d_data);
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