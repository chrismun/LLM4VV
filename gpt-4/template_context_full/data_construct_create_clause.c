#include "acc_testsuite.h"

#ifndef T1
/*T1:data construct create clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int length = 10;
    float* a = (float*)malloc(length * sizeof(float));
    float* b = (float*)malloc(length * sizeof(float));

    for(int i=0; i<length; i++){
        a[i] = (float)rand()/(float)(RAND_MAX/2);  // Initialize with random values
        //a[i] = (float)rand()/(float)(RAND_MAX/2) - 1.f;  // Initialize with random values
        b[i] = 0;  // Initialize with zeros
        //b[i] = 0.f;  // Initialize with zeros
    }
    
    #pragma acc data create(a[0:length])
    {
        #pragma acc parallel loop
        for(int i=0; i<length; i++){
            b[i] = a[i];  // Copy values from array a to array b
        }
    }

    // Verify if values in array a have been copied correctly to array b during the parallel loop
    for(int i=0; i<length; i++){
        if(a[i] != b[i]){
            err = 1;
        }
    }    

    free(a);
    free(b);

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
