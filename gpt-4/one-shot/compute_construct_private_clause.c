#include <stdio.h>
#include <openacc.h>

int main(){
    int failcode = 0;
    int n = 100;
    int a[n];
    int b[n];

    // Initialize the input array 'a' and output array 'b'
    for(int i = 0; i < n; i++){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc parallel loop copyin(a[0:n]) copyout(b[0:n]) private(a)
    for(int i = 0; i < n; i++){
        a[i] = a[i] + 1;
        b[i] = a[i];
    }

    // Validate if the private clause worked correctly
    for(int i = 0; i < n; i++){
        if(b[i] != i + 1){
            printf("Test failed at index %d! Value is %d, but expected %d\n", i, b[i], i + 1);
            failcode = 1;
        }
    }
    
    if(failcode == 0){
        printf("Test passed successfully!\n");
    }

    return failcode;
}