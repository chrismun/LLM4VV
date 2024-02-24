#include <stdio.h>
#include <openacc.h>

#ifndef T1
#define T1
int test1(){
    int err = 0;
    int shared_var = 0;

    #pragma acc parallel num_gangs(1) copy(shared_var)
    {
        #pragma acc loop worker
        for(int i = 0; i < 1000; i++) {
            #pragma acc atomic update
            shared_var++;
        }
    }

    if(shared_var != 1000) {
        err = 1;
        printf("Error: shared_var is %d, expected 1000\n", shared_var);
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}