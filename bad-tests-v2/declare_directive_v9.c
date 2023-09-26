#include "acc_testsuite.h"
#ifndef T2
//T2:kernels,deallocate,V:1.0-2.7
int test2(){
    int err = 0;
    int* a;
    
    #pragma acc declare create(a[0:10])
    a = (int*)malloc(10*sizeof(int));

    for (int i = 0; i< 10; ++i){
        a[i] = i;
    }

    #pragma acc parallel present(a[0:10])
    {
        #pragma acc loop
        for (int i=0;i<10; i++)
        {
           a[i] = a[i]*a[i];
        }
    }

   for (int i=0;i<10; i++)
   {
      if (a[i]!=i*i)
      {
         err += 1;
      }
   }
   
   return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}