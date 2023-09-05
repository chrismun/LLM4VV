#include <stdio.h>
#include <stdlib.h>

void init_array(float* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void print_array(float* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

void validate_copyin(float* arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] != i) {
            printf("Error: Copyin failed!\n");
            return;
        }
    }
    printf("Copyin successful!\n");
}

int main() {
    int n = 10;
    float* host_arr = (float*)malloc(n * sizeof(float));
    init_array(host_arr, n);
    
    float* dev_arr;

    #pragma acc enter data create(dev_arr[0:n])
    #pragma acc data copyin(host_arr[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            dev_arr[i] = host_arr[i];
        }
    }

    validate_copyin(dev_arr, n);

    #pragma acc exit data delete(dev_arr[0:n])

    free(host_arr);
    return 0;
}