#include "acc_testsuite.h"
#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    //Creating the data
    float *a = (float *)malloc(1000*sizeof(float));
    float *d_a;

    //Filling the array
    for(int i = 0; i < 1000; i++){
        a[i] = (float)rand()/(float)(RAND_MAX/10.0);
    }

    
    //Attaching to the device
    #pragma acc enter data create(d_a[0:1000])

    d_a = acc_attach_device((void *)a);
  
    if(d_a == NULL){
        err = 1;
    }
    
    //Detaching from the device
    acc_detach_device((void *)d_a);
  
    //Removing from the device
    #pragma acc exit data delete(d_a[0:1000])

    free(a);

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