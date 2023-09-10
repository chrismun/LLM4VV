#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:kernels construct default clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    int vector_size = 10;
    float* a = (float*)malloc(vector_size*sizeof(float));
    float* b = (float*)malloc(vector_size*sizeof(float));

    for(int i = 0; i < vector_size; ++i){
        a[i] = i;
        b[i] = i;
    }

    #pragma acc kernels loop copy(a[0:vector_size], b[0:vector_size]) default(present)
    for(int i = 0; i < vector_size; ++i){
        b[i] = a[i];
    }

    for(int i = 0; i < vector_size; ++i){
        if(a[i] != b[i]){
            err = 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}