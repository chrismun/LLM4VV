#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:acc update self,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 100;
    int data[size];

    // Initialize data on the host
    for(int i = 0; i < size; i++) {
        data[i] = i;
    }

    // Copy data to the device
    #pragma acc enter data copyin(data[0:size])

    // Update data on the device
    #pragma acc update self(data[0:size])

    // Check if the update was successful
    for(int i = 0; i < size; i++) {
        if(data[i] != i) {
            err = 1;
            break;
        }
    }

    // Copy data back to the host
    #pragma acc exit data delete(data[0:size])

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