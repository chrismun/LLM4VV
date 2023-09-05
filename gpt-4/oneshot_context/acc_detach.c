#include <stdio.h>
#include <openacc.h>

int main()
{
   #pragma acc parallel loop async
   for(int i = 0; i < N; i++)
   {
      // some computation here
   }

   // some operations that should happen while 
   // the parallel region is being computed
   
   #pragma acc wait // waits until the async operations are done

   return 0;
}