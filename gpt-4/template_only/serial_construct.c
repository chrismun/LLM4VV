#include<stdio.h>
#include<openacc.h>

#define SIZE 10000
#define SEED 123

//function to initialize array
void initialize(int* a, int size) {
    srand(SEED);
    for(int i = 0; i < size; i++) {
        a[i] = rand()%2;
    }
}

void compute(int* a, int size) {
    #pragma acc serial loop
    for (int i = 0; i < size; i++) {
        a[i] = a[i] | 1;
    }
}

int verify(int* a, int size) {
    for(int i = 0; i < size; i++) {
        if(a[i] != 1) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int fail = 0;
    int a[SIZE];

    //initialize array
    initialize(a, SIZE);
    
    compute(a, SIZE);
    
    //verify results
    fail = verify(a, SIZE);
  
    printf("Test %s\n", fail ? "Failed" : "Passed");

    return fail;
}