#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main(){
    int i;
    double a[N], b[N], c[N];
    double sum_a = 0.0, sum_b = 0.0, sum_c = 0.0;

    // Initialize arrays a and b
    for(i=0; i<N; i++){
        a[i] = i+1;
        b[i] = i+1;
    }

    // Perform reduction on array a and b and store result in array c
    #pragma acc parallel loop reduction(+:sum_a,sum_b)
    for(i=0; i<N; i++){
        sum_a += a[i];
        sum_b += b[i];
        c[i] = a[i] + b[i];
    }

    // Perform reduction on array c
    #pragma acc parallel loop reduction(+:sum_c)
    for(i=0; i<N; i++){
        sum_c += c[i];
    }

    printf("Sum of array a: %f\n", sum_a);
    printf("Sum of array b: %f\n", sum_b);
    printf("Sum of array c: %f\n", sum_c);

    return 0;
}