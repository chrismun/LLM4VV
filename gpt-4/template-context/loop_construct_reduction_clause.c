#include<stdio.h>
#include<openacc.h>

#define SIZE 100000000

int main()
{
    long long int a[SIZE];
    
    // Initialize a
    for(long long int i=0; i<SIZE; i++)
    {
        a[i] = i;
    }
    
    long long int sum = 0;
    
    // Perform parallel reduction to calculate sum of elements in array a
    #pragma acc parallel loop reduction(+:sum)
    for(long long int i=0; i<SIZE; i++)
    {
        sum += a[i];
    }
    
    printf("Sum is %lld", sum);

    // Check the result
    long long int expected_sum = (SIZE-1)*SIZE/2;
    if(sum != expected_sum)
    {
        printf("Reduction test failed. Expected sum is %lld but got %lld\n", expected_sum, sum);
        return -1;
    }
    
    printf("Reduction test passed\n");
    return 0;
}