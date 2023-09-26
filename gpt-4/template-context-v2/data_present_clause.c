#include "acc_testsuite.h"
#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *data;
    data = (int*)malloc(10*sizeof(int));
    srand(SEED);
    for(int i=0; i<10; i++){
        data[i] = rand();
    }

    #pragma acc data copyin(data[0:10])
    {
        #pragma acc parallel loop
        for(int i=0; i<10; i++){
            data[i] = data[i]+1;
        }

        #pragma acc data present(data[0:10])
        {
            #pragma acc parallel loop
            for(int i=0; i<10; i++){
                data[i] = data[i]+1;
            }
        }
    }
    #pragma acc exit data delete(data[0:10])

    for(int i=0; i<10; i++){
        if(data[i] != (rand()+2)){
            err = 1;
            break;
        }
    }
    free(data);
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