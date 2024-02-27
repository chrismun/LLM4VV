#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 1234
#define n 1000
#define PRECISION 0.001

// Function prototype
int test_acc_init();

int main(){
    int test_result;

    test_result = test_acc_init();

    if(test_result == 0){
        printf("Test Passed: acc_init successfully initialized the device.\n");
    }else{
        printf("Test Failed: acc_init failed to initialize the device properly.\n");
        return 1; // Indicate failure
    }

    return 0; // Indicate success
}

int test_acc_init(){
    // Try to initialize the default accelerator device
    acc_init(acc_device_default);

    // Check if the initialization was successful
    // This can be indirectly observed through subsequent operations, hence a simple kernel execution
    int *hostData = (int*)malloc(n*sizeof(int));
    int err = 0;

    #pragma acc data copy(hostData[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for(int i = 0; i < n; i++){
                hostData[i] = i;
            }
        }
    }

    // Verify data
    for(int i = 0; i < n; i++){
        if(hostData[i] != i){
            err++;
        }
    }

    free(hostData);

    // If there are errors, it might be due to acc_init not working properly
    return err;
}