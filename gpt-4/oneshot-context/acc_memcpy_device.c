#include <stdio.h>
#include <openacc.h>

#define SIZE 10

int main() 
{
    int i;
    int h_a[SIZE];
    int h_b[SIZE];
  
    for (i = 0; i < SIZE; i++) {
        h_a[i] = i + 1;
        h_b[i] = 0;
    }
  
    size_t bytes = SIZE * sizeof(int);
    
    int *d_a = (int*)acc_malloc(bytes);
    int *d_b = (int*)acc_malloc(bytes);
    
    acc_memcpy_to_device(d_a, h_a, bytes); 
    acc_memcpy_to_device(d_b, h_b, bytes); 
  
    acc_memcpy_device(d_b, d_a, bytes);
    
    acc_memcpy_to_host(h_b, d_b, bytes);
  
    for (i = 0; i < SIZE; i++) {
        printf("h_b[%d] = %d\n", i, h_b[i]);
        if(h_b[i] != h_a[i]) 
        {
            printf("Test failed\n");
            return 1;
        }
    }
    printf("Test passed\n");

    acc_free(d_a);
    acc_free(d_b);

    return 0;