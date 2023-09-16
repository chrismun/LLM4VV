#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000
#define DELTA 0.0001

void init(float* a, float* b, int n) {
    for (int i = 0; i < n; ++i){
        a[i] = rand()/(float)RAND_MAX;
        b[i] = rand()/(float)RAND_MAX;
    }
}

void check_results(float* a, float* b, float* c, int n){
    for (int i = 0; i < n; ++i){
        if (abs(a[i] + b[i] - c[i]) > DELTA){
            printf("Test failed at index %d, Expected : %f, Got : %f\n", i, a[i]+b[i], c[i]);
            exit(-1);
        }
    }
    printf("Test passed.\n");
}

void vec_add(float* a, float* b, float* c, int n) {
#pragma acc data copyin(a[0:n],b[0:n]) copy(c[0:n])
    {
#pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            c[i] = a[i] + b[i];
        }
    }
}

int main() {
    float* a = (float*)malloc(N*sizeof(float));
    float* b = (float*)malloc(N*sizeof(float));
    float* c = (float*)malloc(N*sizeof(float));
    
    init(a,b,N);
    
    vec_add(a,b,c,N);
    
    check_results(a,b,c,N);
    
    free(a);
    free(b);
    free(c);
    
    return 0;
}