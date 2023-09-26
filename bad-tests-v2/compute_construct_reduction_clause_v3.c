#include <openacc.h>
#include <stdio.h>

#define N 1000
#define TOLERANCE 0.0001f

int main() {
    int i;
    float sum, psum;
    
    float a[N];
    for(i = 0; i < N; i++)
        a[i] = i + 1;
    
    sum = 0.0f;

    #pragma acc data copyin(a) // copy data to device
    {
        #pragma acc parallel loop reduction(+:sum) // mark parallel region for reduction
        for(i = 0; i < N; i++){
            sum += a[i];
        }
    }

    psum = (N * (N + 1)) / 2; // correct result using formula for sum of integers 1 to N

    // print error if not within tolerance
    if(abs(psum - sum) > TOLERANCE){
        printf("Test failed! Sum is %.5f, but expected %.5f\n", sum, psum);
        return -1;
    }

    printf("Test passed!\n");
    return 0;
}