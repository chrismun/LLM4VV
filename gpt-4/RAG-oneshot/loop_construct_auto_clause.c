#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1000

int main(){

    float *a = (float*) malloc(sizeof(float)*SIZE);
    float *b = (float*) malloc(sizeof(float)*SIZE);
    float *c = (float*) malloc(sizeof(float)*SIZE);

    // Initializing variables
    for(int i=0; i<SIZE; i++){
        a[i] = (float)(rand() % 999) / 100; 
        b[i] = (float)(rand() % 999) / 100; 
        c[i] = 0.0;
    }

    #pragma acc kernels
    {
        #pragma acc loop auto
        for(int i=0; i<SIZE; i++){
            c[i] = a[i] * b[i];
        }
    } // End of ACC kernels

    // Print the results
    for(int i=0; i<10; i++){
        printf("c[%d] = %f\n", i, c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;
}