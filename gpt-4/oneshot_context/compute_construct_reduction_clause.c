#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#define N 100000

int main()
{
    srand(time(NULL));

    float * a = (float *)malloc(N * sizeof(float));
    
    for (int i = 0; i < N; i++) {
        a[i] = (float) rand() / (float)(RAND_MAX);
    }

    float max_val = 0.0;
    
    // Using the reduction clause
    #pragma acc parallel loop reduction(max:max_val)
    for (int i = 0; i < N; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }

    printf("Maximum value in the array = %f\n", max_val);

    free(a);
    
    return 0;
}