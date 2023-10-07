#include "openacc.h" //OpenACC library
#include <stdio.h>

// function to check if two arrays are the same
int check(float *a, float *b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            printf("Arrays do not match at index %d\n", i);
            return 0;
        }
    }
    printf("Arrays match\n");
    return 1;
}

int main() {
    // Initialize host arrays
    int size = 10000;
    float *a = (float*) malloc(size * sizeof(float));
    float *b = (float*) malloc(size * sizeof(float));

    // Initialize device arrays
    float *d_a = NULL, *d_b = NULL;
    int dev_num = acc_get_device_num(acc_device_default);
    acc_set_device_num(dev_num, acc_device_default);
    
    d_a = (float*)acc_malloc(size * sizeof(float));
    d_b = (float*)acc_malloc(size * sizeof(float));

    // Assign and copy to device
    for (int i = 0; i < size; i++) {
        a[i] = (float)i;
    }

    acc_memcpy_to_device(d_a, a, size * sizeof(float));   

    // Perform device-to-device copy
    acc_memcpy_d2d(d_b, d_a, size * sizeof(float), dev_num, dev_num);
    
    // Copy back to host
    acc_memcpy_from_device(b, d_b, size * sizeof(float));

    // Check if the arrays match
    int result = check(a, b, size);

    return result;
}