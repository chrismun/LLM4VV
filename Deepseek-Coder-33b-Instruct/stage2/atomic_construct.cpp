#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:atomic construct,V:2.7-3.3
int test1(){
    int err = 0;
    int shared_var = 0;

    #pragma acc parallel loop copy(shared_var)
    for (int i = 0; i < 1000; i++) {
        #pragma acc atomic update
        shared_var++;
    }

    if (shared_var != 1000) {
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
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}