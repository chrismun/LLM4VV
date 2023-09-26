#include "acc_testsuite.h"

int test_host_data_use_device(){
    int err = 0;
    unsigned int nbytes = 1 << 10;
    char* h_ptr = (char*)malloc(nbytes);
    char* d_ptr;

    // Data setup on host
    for(unsigned int i = 0; i < nbytes; i++) 
        h_ptr[i] = rand();

    // Copy from host to device
    #pragma acc enter data copyin(h_ptr[0:nbytes])
    #pragma acc host_data use_device(h_ptr)
    {
        d_ptr = h_ptr;
    }
    #pragma acc parallel present(h_ptr[0:nbytes])
    {
        #pragma acc loop independent
        for(unsigned int i = 0; i < nbytes; i++)
            h_ptr[i] = h_ptr[i] + 1;
    }
    #pragma acc exit data copyout(h_ptr[0:nbytes])
  
    for(unsigned int i = 0; i < nbytes; i++) {
        if(h_ptr[i] != d_ptr[i] + 1) {
            err = 1;
            break;
        }
    }
    free(h_ptr);
    return err;
}

int main(){
    srand(SEED);
    int n_fails = 0;

    n_fails += test_host_data_use_device();
  
    if(n_fails != 0) {
        printf("Test failed\n");
        return 1;
    }
    printf("Test passed\n");
    return 0;
}