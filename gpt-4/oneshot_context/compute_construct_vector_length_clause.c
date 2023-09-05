#include "acc_testsuite.h"
#include <math.h>

//check vector_length clause
int test1(){
    int err = 0;
    int n = 1000;
    int vector_length = 32;  //set desired vector length

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i){
        a[i] = i;
        b[i] = 2*i;
        c[i] = 0;
    }

   #pragma acc parallel loop  vector_length(vector_length) 
    for (int i = 0; i < n; ++i){
        c[i] = a[i] + b[i];
    }   

    for (int i = 0; i < n; ++i){
        if (c[i] != 3*i ) {
            err+= 1; 
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    
    return err;
}

int main(){
    int error_code = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    
    if (failed != 0){
        error_code += (1 << 0);
    }
    
    return error_code;
}