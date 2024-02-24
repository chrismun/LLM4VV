#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:data construct create clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int *data = new int[N];

    // Initialize data
    for(int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Create data region
    #pragma acc data create(data[0:N])
    {
        // Check if data is correctly created
        for(int i = 0; i < N; i++) {
            if(data[i] != i) {
                err = 1;
                break;
            }
        }
    }

    delete[] data;

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