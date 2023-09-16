#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

void verify(float *data, int size) {
    const float epsilon = 0.0001;
    for(int i = 0; i < size; i++) {
        if(fabs(data[i] - (i+10.0f)) > epsilon) {
            printf("Verification failed at index %d! Got %f, expected %f\n", 
                i, data[i], (float)i+10.0f);
            exit(1);
        }
    }
}

int main() {

    int size = 1024;
    float *data = (float*)malloc(size * sizeof(float));
    
    for(int i = 0; i < size; i++) {
        data[i] = (float)i;
    }

    // Device computations with OpenACC
    #pragma acc enter data copyin(data[0:size]) 

    #pragma acc parallel loop present(data[0:size]) 
    for(int i = 0; i < size; i++) {
        data[i] += 10.0f;
    }
    #pragma acc exit data copyout(data[0:size]) 

    // Verification
    verify(data, size);

    printf("Verification successful! The results are correct.\n");

    // Free host memory
    free(data);

    return 0;
}