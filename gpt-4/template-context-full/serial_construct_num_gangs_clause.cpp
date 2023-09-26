#include "acc_testsuite.h"
#include <math.h>
#include <openacc.h>

#ifndef T1
/*T1:serial construct num_gangs clause,V:2.0-2.7*/

int test1(){
    int err = 0;
    int num_gangs = 50;
    srand(SEED);
    
    unsigned *h_array = (unsigned*)malloc(num_gangs * sizeof(unsigned));
    for(int i = 0; i < num_gangs; i++)
    {
        h_array[i] = 1;
    }

    unsigned *d_array = acc_copyin(h_array, num_gangs * sizeof(unsigned));

    #pragma acc serial num_gangs(num_gangs) 
    for(int i = 0; i < num_gangs; i++)
    {
        h_array[i] *= 2;
    }

    acc_memcpy_from_device(h_array, d_array, num_gangs * sizeof(unsigned));

    for(int i = 0; i < num_gangs; i++)
    {
        if(h_array[i] != 2){
            err = 1;
        }
    }

    acc_delete(h_array, num_gangs * sizeof(unsigned));
    free(h_array);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if(failed != 0){
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}