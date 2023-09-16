#include <stdio.h>
#include <openacc.h>

int test() {
    int N = 100;
    float a[N], b[N], c[N];
    int err = 0;

    // Initialize data
    for(int i=0; i<N; i++) {
        a[i] = i+1;
        b[i] = (i+1) * 2;
        c[i] = 0;
    }

    // Parallel compute using OpenACC
    #pragma acc parallel loop
    for(int i=0; i<N; i++) {
        c[i] = a[i] + b[i];
    }

   // Check
   for(int i=0; i<N; i++) {
       if(c[i] != a[i] + b[i]) {
            err++;
       }
    }

    // Error rate
    if(err > 0) {
        printf("Errors: %d\n",err);
        return 1;
    }else{
        printf("No Errors\n");
        return 0;
    }
}

int main() {
    // Perform tests
    int error = test();
  
    // Return
    if(error){
        printf("Test failed\n");
        return 1;
    }else{
        printf("Test passed\n");
        return 0;
    }
}