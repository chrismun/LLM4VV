#include <stdio.h>
#include <openacc.h>

#define N 100000
#define TOLERANCE 1e-5 

// Function to compare results to check for any discrepancies
void checkResult(float* res, float* ref)
{
    for(int i = 0; i < N; i++){
        if(abs(res[i] - ref[i]) > TOLERANCE){
            printf("Test failed at index %d\n", i);
            exit(1);
        }
    }
    printf("Test passed!\n");
}

//Kernel
void vectorAdd(float* A, float* B, float* C, int n)
{   
#pragma acc parallel loop copyin(A[0:n],B[0:n]) copyout(C[0:n]) 
    for(int i = 0; i < n; i++){
        C[i] = A[i] + B[i];
    }
}

int main()
{
    float A[N], B[N], C[N], ref_C[N];
    
    // Initialize input vectors
    for(int i = 0; i < N; i++){
        A[i] = (float)rand()/(float)(RAND_MAX);
        B[i] = (float)rand()/(float)(RAND_MAX);
        ref_C[i] = A[i] + B[i]; 
    }

    //launch kernel
    vectorAdd(A, B, C, N);

    //Check result
    checkResult(C, ref_C);

    return 0;
}