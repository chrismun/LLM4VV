#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:acc malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a;
    int size = rand() % 10000;

    a = (int*)acc_malloc(size * sizeof(int));
    if (a == NULL){
        printf("acc_malloc failed to allocate memory\n");
        err = 1;
    }
    else{
        acc_free(a);
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