#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int gangs = 128;
    int *a = (int*)malloc(gangs*sizeof(int));
    int *b = (int*)malloc(gangs*sizeof(int));
  
    for(int i=0;i<gangs;++i){
        a[i] = 0;
        b[i] = i;
    }
    #pragma acc parallel loop gang worker vector present(a[0:gangs],b[0:gangs])
       for (int x = 0; x < gangs; ++x) {
            a[x] = x;
            b[x] = __pgi_gangidx();
       }
    for(int i=0;i<gangs;++i){
        if(a[i] != b[i]){
          err = 1;
          break;
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