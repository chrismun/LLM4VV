#include <iostream>
#include <cstdlib>
#include <ctime>

#define T1
#define SEED time(NULL)
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:serial construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int original = 5;
    int copy = original;

    #pragma acc parallel loop firstprivate(copy)
    for(int i = 0; i < NUM_TEST_CALLS; i++) {
        copy += i;
    }

    if(copy != original) {
        err = 1;
    }

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