#include <stdio.h>
#include <openacc.h>
#include <math.h>

#define ARRAY_SIZE 1000000
#define TOLERANCE 0.01

void init_array(float *a, float *b, float *c) {
    int i;
    for (i=0; i<ARRAY_SIZE; i++) {
        a[i] = (float)i+1;
        b[i] = (float)ARRAY_SIZE-i;
        c[i] = 0.0f;
    }
}

float verify_result(float *a) {
    int i;
    float sum = 0.0f;
    for (i=0; i<ARRAY_SIZE; i++) {
        sum += a[i];
    }
    return sum;
}

int main() {
    float *a = (float*)malloc(sizeof(float)*ARRAY_SIZE);
    float *b = (float*)malloc(sizeof(float)*ARRAY_SIZE);
    float *c = (float*)malloc(sizeof(float)*ARRAY_SIZE);

    init_array(a, b, c);

    #pragma acc parallel loop copyin(a[0:ARRAY_SIZE], b[0:ARRAY_SIZE]) copyout(c[0:ARRAY_SIZE])
    for(int i=0; i<ARRAY_SIZE; i++) {
        c[i] = a[i] + b[i];
    }

    float result = verify_result(c);
    float expected = ARRAY_SIZE*(ARRAY_SIZE+1);

    if(fabs(result-expected)/expected < TOLERANCE) {
        printf("Test passed!\n");
        return 0;
    } else {
        printf("Test failed! expected=%f, result=%f\n", expected, result);
        return -1;
    }
}