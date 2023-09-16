#include "acc_testsuite.h"
#include <math.h>
#include <stdio.h>

#define TOLERANCE 0.000001

// Function to test
void test_first_private(){
    int isTestPass = 1;
    float a = 1.0;
    float b = 0.0;
    
    // Implement OpenACC directive
    #pragma acc parallel firstprivate(a)
    {
        b = a;
        a = 5.0;
    }
    
    // Validate the value of 'b'
    if (fabs(b - 1.0) > TOLERANCE){
        isTestPass = 0;
    }
    
    // The value of 'a' should not change as it is private
    if (fabs(a - 1.0) > TOLERANCE){
        isTestPass = 0;
    }
    
    // Print test result
    if (isTestPass){
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

}

// Main function
int main(){
    test_first_private();
    return 0;
}