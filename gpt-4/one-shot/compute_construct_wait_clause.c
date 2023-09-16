// Including acc_testsuite library, which provides standard test functionalities.
#include "acc_testsuite.h"

real_t* init_array(int size) {
    srand(SEED);
    real_t *a = (real_t *)malloc(size * sizeof(real_t));
   
    for (int i = 0; i < size; ++i){
        a[i] = rand() / (real_t)(RAND_MAX / 10);
    }

   return a;
}

int test_copyout(real_t *a, int size) {
    int err = 0;
    // Initiating another array
    real_t *b = (real_t *)malloc(size * sizeof(real_t));

    // Copy the data of array 'a' to device memory.
    #pragma acc data copyin(a[0:size])
    {
        // Then copy into 'b' on device memory and fetch back to host.
        #pragma acc kernels copyout(b[0:size])
        {
            #pragma acc loop
            for (int x = 0; x < size; ++x){
                b[x] = a[x];
            }
        }
    }

    // Check if the array 'b' has been properly copied from 'a'.
    for (int x = 0; x < size; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    free(b);
    return err;
}

int main(){
    int n = 10000;
    
    real_t* a = init_array(n);
   
    // Test the copyout clause
    int err = test_copyout(a, n);
   
    if (err != 0){
      printf("CopyOut clause test failed with %d errors. \n", err);
    } else {
      printf("CopyOut clause test passed successfully. \n");
    }

    free(a);
    return err;
}