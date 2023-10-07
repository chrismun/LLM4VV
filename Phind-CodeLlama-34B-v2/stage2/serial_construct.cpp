#include <iostream>
#include <cstdlib>
#include <cmath>
#include "acc_testsuite.h"

using namespace std;

#ifndef T1
/*T1:serial construct,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    const int array_size = 100;
    int array[array_size];
    int host_array[array_size];

    for (int x = 0; x < array_size; ++x){
        array[x] = rand() % 100;
        host_array[x] = array[x];
    }

    int constant = rand() % 100;

    #pragma acc serial
    {
        #pragma acc loop
        for (int x = 0; x < array_size; ++x){
            array[x] += constant;
        }
    }

    for (int x = 0; x < array_size; ++x){
        host_array[x] += constant;
    }

    for (int x = 0; x < array_size; ++x){
        if (array[x] != host_array[x]){
            err = 1;
            break;
        }
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