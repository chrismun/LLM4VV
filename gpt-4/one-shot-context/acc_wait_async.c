#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,data,data-region,V:1.0-2.7
void async_test(){
    int isPassed = 1;
    srand(SEED);
    int *arr1 = (int *) malloc(n * sizeof(int));
    int *arr2 = (int *) malloc(n * sizeof(int));

    for(int x = 0; x < n; ++x){
        arr1[x] = rand() / RAND_MAX * 100;
        arr2[x] = 0;
    }

    int async1 = 1;
    int async2 = 2;
    #pragma acc data copyin(arr1[0:n]) copyout(arr2[0:n])
    {
        #pragma acc parallel loop async(async1)
        for(int x = 0; x < n; ++x){
            arr2[x] = arr1[x] * 2;
        }
        #pragma acc parallel loop async(async2)
        for(int x = 0; x < n; ++x){
            arr2[x] += arr1[x];
        }
        acc_wait_async(async1, async2); // Waiting for both operations to finish
    }

    for(int x = 0; x < n; ++x){
        if(arr2[x] != 3 * arr1[x]){
            isPassed = 0;
        }
    }

    if (isPassed == 1){
        printf("Test Passed.\n");
    }
    else{
        printf("Test Failed.\n");
    }
}
#endif

int main(){
    async_test();
    return 0;
}