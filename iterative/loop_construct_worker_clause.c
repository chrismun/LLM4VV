#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1000;
    int data[size];
    int sum = 0;

    for(int i = 0; i < size; i++) {
        data[i] = rand() % 100;
    }

    #pragma acc data copy(data[:size])
    {
        #pragma acc parallel loop worker
        for(int i = 0; i < size; i++) {
            sum += data[i];
        }
    }

    for(int i = 0; i < size; i++) {
        sum -= data[i];
    }

    if(sum != 0) {
        err++;
        printf("Error: Sum is not zero\n");
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