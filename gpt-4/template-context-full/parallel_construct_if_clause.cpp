#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:parallel construct if clause,V:2.0-2.7*/
int test1() {
   int err = 0;
   srand(SEED);
   int* a = (int*)malloc(sizeof(int) * 10000);
   int* a_device = new int[10000];
   
   for (int i = 0; i < 10000; ++i) {
       a[i] = rand();
   }
   
   #pragma acc enter data create(a_device[0:10000])
   #pragma acc parallel if(a[0] > a[1]) copyin(a[0:10000]) copyout(a_device[0:10000])
   for (int i = 0; i< 10000; ++i) {
       a_device[i] = a[i];
   }

   for (int i = 0; i < 10000; ++i) {
       if(a[i] != a_device[i]){
           err = 1;
           break;
       }
   }

   free(a);
   delete[] a_device;
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