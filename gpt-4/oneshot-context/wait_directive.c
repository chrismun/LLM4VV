#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define NUM 10

int main() {
    int* a_h, *b_h, *c_h;
    int* a_d, *b_d, *c_d;
    int errors = 0;

    a_h = (int*)malloc(SIZE * sizeof(int));
    b_h = (int*)malloc(SIZE * sizeof(int));
    c_h = (int*)malloc(SIZE * sizeof(int));

    // Initialization of input vectors
    for(int i = 0; i < SIZE; i++) {
        a_h[i] = rand() % NUM;
        b_h[i] = rand() % NUM;
        c_h[i] = 0;
    }

    #pragma acc data copyin(a_h[0:SIZE], b_h[0:SIZE]) copyout(c_h[0:SIZE])
    {
        #pragma acc parallel loop async(1)
        for(int i=0; i<SIZE; i++){
            c_h[i] = a_h[i] + b_h[i];
        }
        
        #pragma acc wait(1)

        #pragma acc parallel loop async(2)
        for(int i=0; i<SIZE; i++){
            c_h[i] = c_h[i] * NUM;
        }
        
        #pragma acc wait(2)
    }

    // Check correctness
    for(int i=0; i<SIZE; i++){
        if(c_h[i] != (a_h[i] + b_h[i]) * NUM){
            errors++;
        }
    }

    if(errors > 0)
        printf("FAILED\n");
    else
        printf("PASSED\n");

   free(a_h);
   free(b_h);
   free(c_h);

   return 0;
}