#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *h_data = new int[SIZE];
    int *d_data;

    // initialize h_data
    for(int i=0; i<SIZE; i++) { h_data[i] = rand()%SIZE; }

    // OpenACC create clause
    #pragma acc enter data create(d_data[0:SIZE])

    // Check if d_data has been created on device
    if(acc_is_present(d_data, SIZE*sizeof(int)) == 0) {
        err = 1;
    }

    // Cleanup
    #pragma acc exit data delete(d_data[0:SIZE])
    delete[] h_data;
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