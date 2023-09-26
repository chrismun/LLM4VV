#include <stdio.h>
#define N 100000

int main()
{
    // Initialize an array
    float a[N];
    for(int i = 0; i < N; i++){
        a[i] = (float)i;
    }

    #pragma acc data copy(a)
    {
        #pragma acc parallel loop vector(32)
        for(int i = 0; i < N; i++){
            a[i] = a[i] * a[i];
        }
    }

    // Validate
    int error = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] != (float)(i*i)) {
            printf("Found difference at %d a[i] = %f\n", i, a[i]);
            error++;
            break;
        }
    }

    if (error) {
        printf("Validation failed.\n");
    }
    else{
        printf("Validation succeeded.\n");
    }

    return 0;