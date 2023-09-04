#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int x = rand() % 100;
    int y = rand() % 100;
    int z = x + y;

    #pragma acc atomic update
    x = x + y;

    if (x != z){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}