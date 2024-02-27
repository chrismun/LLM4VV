#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <time.h>

// Adjust the size for significant time measurement
#define N 1000000

double performAutoLoop(int *a, int length) {
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    #pragma acc kernels
    {
        // The 'auto' clause is implicit for loops inside kernels without a specified clause.
        #pragma acc loop auto
        for(int i = 0; i < length; i++) {
            a[i] += 1;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int* generateData(int n) {
    int* data = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        data[i] = i;
    }
    return data;
}

int main() {
    int* data = generateData(N);
    double time_taken = performAutoLoop(data, N);
    printf("Time taken for auto loop: %f seconds\n", time_taken);

    free(data);
    return 0;
}