#include <stdio.h>
#include <openacc.h>

#define SIZE 1000
#define TILE_SIZE 100

int main()
{
    int a[SIZE];

    #pragma acc parallel loop tile(TILE_SIZE)
    for(int i = 0; i < SIZE; i++)
    {
        a[i] = i;
    }

    // Check results
    for(int i = 0; i < SIZE; i++)
    {
        if(a[i] != i)
        {
            printf("Test failed at index %d. Expected %d but got %d\n", i, i, a[i]);
            return -1;
        }
    }

    printf("Test passed!\n");

    return 0;
}