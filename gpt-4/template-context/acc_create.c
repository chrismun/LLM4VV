#include <stdio.h>
#include <openacc.h>
#include <assert.h>

#define SIZE 1000

// Helper function to populate an array
void fillArray(int* a, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }
}

// Test function for acc_copyin
void test_acc_copyin() 
{
    int h_data[SIZE], *d_data;
    fillArray(h_data, SIZE);

    // Copy to device
    d_data = acc_copyin(h_data, SIZE * sizeof(int));

    // Launch kernel
    #pragma acc parallel loop present(d_data[0:SIZE])
    for (int i = 0; i < SIZE; i++) {
        d_data[i] *= 2;
    }

    // Test correct values
    acc_copyout(h_data, SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        assert(h_data[i] == 2 * i);
    }

    fprintf(stdout, "acc_copyin test passed.\n");
}

// Test function for acc_create
void test_acc_create() 
{
    int h_data[SIZE], *d_data;
    fillArray(h_data, SIZE);

    // Allocate memory on device
    d_data = acc_create(h_data, SIZE * sizeof(int));

    // Launch kernel
    #pragma acc parallel loop present(d_data[0:SIZE])
    for (int i = 0; i < SIZE; i++) {
        d_data[i] = h_data[i] * 2;
    }

    // Test correct values
    acc_copyout(h_data, SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++) {
        assert(h_data[i] == 2 * i);
    }

    fprintf(stdout, "acc_create test passed.\n");
}

int main() 
{
    test_acc_copyin();
    test_acc_create();
    return 0;
}