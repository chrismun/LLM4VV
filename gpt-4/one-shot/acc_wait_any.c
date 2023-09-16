#include <stdio.h>
#include <openacc.h>

void test_wait_any(int size) 
{
 float* a = (float*) malloc(sizeof(float)*size);
 float* b = (float*) malloc(sizeof(float)*size);

 #pragma acc kernels async(1)
 for (int i=0; i<size; i++)
   a[i] = (float)i;

 #pragma acc kernels async(2) 
 for (int i=0; i<size; i++) 
   b[i] = (float)i*2.0f;

 // Waiting for any of the above operations to complete
 #pragma acc wait 

 // Checking if the values are correct 
 for (int i = 0; i < size; i++) 
 {
  if (a[i] != (float)i || b[i] != (float)i*2.0f) 
  {
    printf(" Test Failed \n"); 
    return;
  }
 }

 printf(" Test Passed \n");
}

int main(int argc, char* argv[]) 
{
 int size = 10000;
 test_wait_any(size);
 return 0;
}