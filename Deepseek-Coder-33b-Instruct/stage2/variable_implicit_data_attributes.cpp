#include <iostream>
#include <omp.h>

#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    int a = 10;

    #pragma omp parallel shared(a)
    {
        #pragma omp single
        {
            a = 20;
        }
    }

    if (a != 20) {
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