#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef T1
/*T1:kernels construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    int arr_size = 1000;
    int *arr = (int*)malloc(sizeof(int)*arr_size);
    
    srand(SEED);

    //Initialization
    for(int i=0; i<arr_size; i++)
      arr[i] = rand() % arr_size;
  
    #pragma acc kernels copy(arr[0:arr_size])
    for(int i=0; i<arr_size; i++)
      arr[i] *= 2;
      
    //Testing
    for(int i=0; i<arr_size; i++){
       if(arr[i] >= 2*arr_size || arr[i] < 0){
           err = 1;
       }
    }

    free(arr);
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