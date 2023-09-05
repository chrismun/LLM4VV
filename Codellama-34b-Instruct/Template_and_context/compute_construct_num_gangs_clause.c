#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = rand() % 10 + 1;
    int num_workers = rand() % 10 + 1;
    int num_vectors = rand() % 10 + 1;

    acc_parallel(num_gangs, num_workers, num_vectors){
        // Do some work here
    }

    if (num_gangs != acc_get_num_gangs()){
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