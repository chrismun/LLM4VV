#include <stdlib.h>
#include <string.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Delete the data using acc_delete
    acc_delete(data, sizeof(int) * 10);

    // Check that the data has been deallocated
    if (data != NULL) {
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