#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void vector_add(int n, float *a, float *b, float *c, int async_id) {
    #pragma acc parallel loop present(a, b, c) async(async_id)
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int n = 100000;
    float *a, *b, *c;
  
    // Allocate memory
    a = (float *)malloc(n * sizeof(float));
    b = (float *)malloc(n * sizeof(float));
    c = (float *)malloc(n * sizeof(float));
  
    // Initialize input vectors
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = n - i;
    }
  
    // Initialize output vector
    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }
  
    // Calculate vector sum asynchronously
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        int async_id = acc_async_test_all();
        vector_add(n, a, b, c, async_id);
    }
  
    // Wait for all async tasks to complete
    acc_wait_all();
  
    // Print the first 10 elements of the output vector
    for (int i = 0; i < 10; i++) {
        printf("%f ", c[i]);
    }
    printf("\n");
  
    // Free memory
    free(a);
    free(b);
    free(c);
  
    return 0;