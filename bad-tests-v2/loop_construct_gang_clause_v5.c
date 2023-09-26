#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main()
{
    int i, failed = 0;
    int *a, *b, *c;

    a = (int*) malloc(SIZE*sizeof(int));
    b = (int*) malloc(SIZE*sizeof(int));
    c = (int*) malloc(SIZE*sizeof(int));

    // Initialize arrays
    for(i = 0; i < SIZE; i++)
    {
        a[i] = i+1;
        b[i] = i+1;
        c[i] = 0;
    }

    // OpenACC loop
    #pragma acc parallel loop copyin(a[0:SIZE],b[0:SIZE]) copyout(c[0:SIZE]) num_gangs(50) vector_length(1)
    for(i = 0; i < SIZE; i++)
    {
        #pragma acc loop gang
        for (int j = 0; j < SIZE; j++)
            c[i] += a[j]*b[j];
    }

    // Verify
    for(i = 0; i < SIZE; i++)
    {
        if(c[i] != ((i+1)*(i+1)))
            failed = 1;
    }

    free(a); free(b); free(c);

    return failed;   
}