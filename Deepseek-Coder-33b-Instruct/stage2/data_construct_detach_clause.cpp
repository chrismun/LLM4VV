#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));

    const int size = 100;
    int *data = new int[size];

    #pragma acc data copy(data[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; i++) {
            data[i] = rand() % 100;
        }

        #pragma acc update host(data[0:size])
    }

    // Check if data is copied back to the host
    for(int i = 0; i < size; i++) {
        if(data[i] == 0) {
            err = 1;
            break;
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