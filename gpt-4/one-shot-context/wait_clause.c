#include<stdlib.h>
#include<stdio.h>
#include<openacc.h>

int main()
{
    // size of array
    int n = 1<<20;
    
    float *a = (float*)malloc(n*sizeof(float));
    float *b = (float*)malloc(n*sizeof(float));
    
    // fill the array with initial values
    for(int i = 0; i < n; i++)
    {
        a[i] = 1.0f;
        b[i] = 0.0f;
    }
    
    // Create an asynchronous queue
    #pragma acc async(1)
    
    // Copy array 'a' to the device. Do this asynchronously with respect to the host
    #pragma acc enter data copyin(a[0:n]) async(1)
    
    #pragma acc async(2)
    // Launch the kernel to add 1 to each element of the array 'a'
    #pragma acc kernels present(a)
    for (int i=0; i<n; i++){
        a[i] += 1;
    }
    
    
    // The 'wait' directive will ensure that all preceding operations (in this case, the addition kernel) 
    // have completed before continuing on the host.
    #pragma acc wait(2)
    
    // Copy the modified array 'a' back to the host
    #pragma acc exit data copyout(a[0:n])
    
    // Print the modified array
    for(int i=0; i<n; i++)
    {
        printf("a[%d]=%f\n", i, a[i]);
    }

    return 0;
}