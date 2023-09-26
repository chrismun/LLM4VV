#include "acc_testsuite.h"
#ifndef T1
/*T1:data construct delete clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b;
    int len = 1<<16;
    
    a = (int*) malloc(len*sizeof(int));
    b = (int*) malloc(len*sizeof(int));
    
    /*Initialization*/
    for (int i=0; i < len; i++){
        a[i] = rand() % 1024;
    }

    /* Copy data to the device */
    #pragma acc enter data copyin(a[0:len])

    /* Modify data on the device */
    #pragma acc parallel loop present(a[0:len])
    for (int x = 0; x < len; x++) {
        a[x] += 5;
    }
    
    /* Copy data from device to host */
    #pragma acc exit data copyout(a[0:len])
    
    /* Delete data from device */
    #pragma acc exit data delete(a)
    
    /* Check if modification is correct, and mark error if not */
    for (int x=0; x < len; x++){
        if(a[x] != b[x] + 5){
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