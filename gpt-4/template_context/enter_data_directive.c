#include "acc_testsuite.h"

int test_enter_data() {
    int err = 0;
    int* h_array = (int*)malloc(100*sizeof(int));
    int* d_array;

    // Initialize host array
    for(int i=0; i<100; i++) {
       h_array[i] = i;
    }

    // Examine whether data is correctly entered into device
    #pragma acc enter data create(h_array[0:100])
    #pragma acc parallel present(h_array)
    {
        d_array = acc_deviceptr(h_array);
    }

    // Check if data is on device
    if(d_array == NULL) {
        err = 1;
    }

    // Remove data from device
    #pragma acc exit data delete(h_array)

    free(h_array);
    return err;
}

int main() {
    int error_code = 0;
    int failed;

    failed = test_enter_data();

    if (failed != 0) {
        error_code = (1 << 0);
    }

    return error_code;
}