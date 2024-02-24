#include <iostream>
#include <cstdlib>
#include <ctime>
#include <openacc.h>

#ifndef T1
//T1:parallel construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(0));

    const int size = 1000;
    int data[size];
    int result[size];

    // Initialize data
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 100;
    }

    // Parallel region with num_workers clause
    #pragma acc parallel num_workers(4) copy(data[0:size]) copyout(result[0:size])
    {
        #pragma acc loop
        for (int i = 0; i < size; ++i) {
            result[i] = data[i] * 2;
        }
    }

    // Verify the results
    for (int i = 0; i < size; ++i) {
        if (result[i] != data[i] * 2) {
            err = 1;
            break;
        }
    }

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