#include "acc_testsuite.h"
#ifndef T1
/*T1:variable predetermined data attributes,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
  
    int len=1024;
    int *a=(int *)malloc(sizeof(int)*len);
    int *b=(int *)malloc(sizeof(int)*len);
    for(int i=0;i<len;i++){
        a[i] = rand();
        b[i] = a[i];
    }
    
    bool success=true;
    #pragma acc parallel loop copy(a[0:len])
    for(int i=0;i<len;i++){
        a[i] *= 2;
        if(a[i] != 2*b[i]) success=false;
    }

    if(!success){
        err = 1;
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