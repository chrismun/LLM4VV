#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define vector size
#define SIZE 1000

// Vector addition function with pointers replaced by a lower-level CUDA kernel
__global__ void add(int *a, int *b, int *c) {
    int tid = blockIdx.x;    // this thread handles the data at its thread id
    if (tid < SIZE)
        c[tid] = a[tid] + b[tid];
}

int main() {
    int a[SIZE], b[SIZE], c[SIZE];
    int *dev_a, *dev_b, *dev_c;

    // allocate the memory on the GPU
    acc_init(acc_device_default);
    dev_a = (int*)acc_malloc(sizeof(int) * SIZE);
    dev_b = (int*)acc_malloc(sizeof(int) * SIZE);
    dev_c = (int*)acc_malloc(sizeof(int) * SIZE);

    // fill the arrays 'a' and 'b' on the CPU
    for (int i = 0; i < SIZE; i++) {
        a[i] = -i;
        b[i] = i * i;
    }

    // copy the arrays 'a' and 'b' to the GPU
    acc_copyin(a, SIZE * sizeof(int));
    acc_copyin(b, SIZE * sizeof(int));

    #pragma acc host_data use_device(dev_a, dev_b, dev_c)
    {
        // call 'add' kernel
        add<<<SIZE,1>>>(dev_a, dev_b, dev_c);
    }

    // copy the array 'c' back from the GPU to the CPU
    acc_copyout(c, SIZE * sizeof(int));

    // verify the result
    int correct = 1;
    for (int i = 0; i < SIZE; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error: value of c[%d] = %d, expected %d\n", i, c[i], a[i] + b[i]);
            correct = 0;
        }
    }

    // free the memory allocated on the GPU
    acc_free(dev_a);
    acc_free(dev_b);
    acc_free(dev_c);

    if (correct) {
        printf("GPU computation is correct.\n");
    }

    acc_shutdown(acc_device_default);
    return 0;
}