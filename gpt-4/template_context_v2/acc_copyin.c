#include "acc_testsuite.h"
#ifndef T1
//T1:acc copyin,V:2.7-3.3
int test1(){
    int err = 0;
    int* h_a;
    int* d_a;
    int size = 1024;
    
    h_a = (int*)malloc(size * sizeof(int));
    d_a = (int*)malloc(size * sizeof(int));
    
    srand(SEED);
    for(int i = 0; i < size; ++i){
        h_a[i] = rand() % 100;
    }

    #pragma acc enter data copyin(h_a[0:size])

    copy_function(h_a, d_a, size); // Notice that you should write this function under OpenACC directives
    
    #pragma acc exit data delete(h_a)

    for(int i = 0; i < size; ++i){
        if(h_a[i] != d_a[i]){
            err = 1;
        }
    }

    free(h_a);
    free(d_a);

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