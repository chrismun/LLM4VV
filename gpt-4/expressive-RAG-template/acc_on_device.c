#include "acc_testsuite.h"
#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

   // Number of elements in arrays
   int n = 10000;
   float *a;
   float *b;

   // Allocate space for device copies of a, b
   a = (float *)malloc(n*sizeof(float));
   b = (float *)malloc(n*sizeof(float));

   // Setup input values   
   for (int i = 0; i < n; i++) {
           a[i] = (float)rand() / (float)RAND_MAX;
   }
   #pragma acc enter data create(a[0:n])
   #pragma acc kernels deviceptr(a)
   {
       for (int i = 0; i < n; i++){
           b[i] = a[i];
       }
   }
   #pragma acc exit data delete(a[0:n])

    //Verify results on host
   for (int i = 0; i < n; i++){
       if(a[i] != b[i]){
           err = 1;
           break;
        }
    }

   // Cleanup memory
   free(a); 
   free(b);
   return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}