#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openacc.h>

// Utility function for initialization
void initialize_array(int* array, int length, int val) {
    for(int i = 0; i < length; ++i) {
        array[i] = val;
    }
}

// Test for OpenACC 'attach' clause
int test_attach_clause() {
    int err = 0;
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));

    // Initialize array
    initialize_array(a, size, 1);
    
    // OpenACC region where 'a' is attached.
    #pragma acc data copy(a[0:size]) attach(a)
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; ++i) {
            a[i] += 1; // Modify the array within the device
        }
    } // Implicit detach happens here

    // Verify the modifications
    for(int i = 0; i < size; ++i) {
        if(a[i] != 2) {
            err = 1; // Error if the array was not correctly modified
            break;
        }
    }
    
    // Clean up
    free(a);
    
    return err;
}

int main(){
    int result = test_attach_clause();
    if(result == 0){
        printf("OpenACC 'attach' clause test PASSED.\n");
    } else {
        printf("OpenACC 'attach' clause test FAILED.\n");
    }
    return result;
}