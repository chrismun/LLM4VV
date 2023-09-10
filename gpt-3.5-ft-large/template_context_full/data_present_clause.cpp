#include "acc_testsuite.h"
#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){

        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2:data present clause,V:2.7-3.3
int test2(){
    int err = 0;
    srand(2*SEED);

    return err;
}
#endif

#ifndef T3
//T3:data present clause,V:2.7-3.3
int test3(){
    int err = 0;
    srand(3*SEED);
    int* a = (int *)malloc(10 * n * sizeof(int));
    real_t* b = (int *)malloc(n * sizeof(real_t));
    
    return err;
}
#endif

#ifndef T4
//T4:data present clause,V:2.7-3.3
int test4(){
    int err = 0;
    srand(4*SEED);
 
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif  
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif   
    return failcode;
}