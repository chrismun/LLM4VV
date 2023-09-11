#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int x = rand() % 100;
    int y = rand() % 100;
    int z = rand() % 100;

    #pragma acc atomic read
    x = x + y;

    #pragma acc atomic write
    y = x + z;

    #pragma acc atomic update
    z = x + y;

    #pragma acc atomic capture
    {
        x = x + y;
        y = x + z;
        z = x + y;
    }

    if (x != y || y != z || z != x){
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