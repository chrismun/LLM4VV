#include <stdlib.h>
#include <stdio.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    if(){
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

void* acc_malloc(size_t bytes) {
    void* ptr = NULL;
    if (bytes > 0) {
        ptr = malloc(bytes);
        if (ptr == NULL) {
            printf("Error: acc_malloc failed to allocate %zu bytes\n", bytes);
            return NULL;
        }
    }
    return ptr;
}