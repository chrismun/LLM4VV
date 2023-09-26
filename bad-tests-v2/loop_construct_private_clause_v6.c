#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

void verify(float *a, float *b, float *c, int n, float div)
{
    int i, j, k;

    for (k = 0; k < n; k++)
    {
        for (j = 0; j < n; j++)
        {
            float tmp = b[j*n + k] + c[j*n + k];
            for (i = 0; i < n; i++)
            {
                a[i*n*n + j*n + k] += tmp / div;
            }
        }
    }
}

int main()
{
    float *a, *b, *c;
    int i, j, k;

    a = (float *)malloc(SIZE * SIZE * SIZE * sizeof(float));
    b = (float *)malloc(SIZE * SIZE * sizeof(float));
    c = (float *)malloc(SIZE * SIZE * sizeof(float));

    for (k = 0; k < SIZE; k++)
    {
        for (j = 0; j < SIZE; j++)
        {
            b[j*SIZE + k] = rand() / (float)RAND_MAX;
            c[j*SIZE + k] = rand() / (float)RAND_MAX;
            for (i = 0; i < SIZE; i++)
            {
                a[i*SIZE*SIZE + j*SIZE + k] = rand() / (float)RAND_MAX;
            }
        }
    }

    #pragma acc data copyin(b[0:SIZE*SIZE], c[0:SIZE*SIZE]) copy(a[0:SIZE*SIZE*SIZE])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang
            for (k = 0; k < SIZE; k++)
            {
                #pragma acc loop worker private(tmp)
                for (j = 0; j < SIZE; j++)
                {
                    float tmp = b[j*SIZE + k] + c[j*SIZE + k];
                    #pragma acc loop vector
                    for (i = 0; i < SIZE; i++)
                    {
                        a[i*SIZE*SIZE + j*SIZE + k] += tmp / SIZE;
                    }
                }
            }
        }
    }

    verify(a, b, c, SIZE, SIZE);

    for (k = 0; k < SIZE; k++)
    {
        for (j = 0; j < SIZE; j++)
        {
            for (i = 0; i < SIZE; i++)
            {
                if (a[i*SIZE*SIZE + j*SIZE + k] != a[i*SIZE*SIZE + j*SIZE + k])
                {
                    printf("Test failed\n");
                    return 1;
                }
            }
        }
    }

    printf("Test passed\n");

    return 0;