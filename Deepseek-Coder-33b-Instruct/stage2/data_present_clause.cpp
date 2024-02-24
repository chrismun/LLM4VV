#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int size = 100;
    int *data = (int*)malloc(size * sizeof(int));

    // Initialize data
    for(int i = 0; i < size; i++) {
        data[i] = i;
    }

    // Use OpenACC to copy data to the device
    #pragma acc data copyin(data[0:size])
    {
        // Use the data present clause to ensure that the data is present on the device
        #pragma acc data present(data[0:size])
        {
            // Check that the data is present on the device
            #pragma acc kernels
            for(int i = 0; i < size; i++) {
                if(data[i] != i) {
                    err = 1;
                    break;
                }
            }
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