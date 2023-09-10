#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    int lengthless1 = 0;
    int device_num = 0;
    size_t device_num_length = 1;

    int* a = (int *)malloc(n * sizeof(int));
    int** has_equal;

    has_equal = (int **)malloc(device_num_length * sizeof(int *));
    for (int x = 0; x < device_num_length; ++x){
        has_equal[x] = (int *)malloc(10 * sizeof(int));
        for (int y = 0; y < 10; ++y){
            has_equal[x][y] = 0;
        }
    }

    for (int x = 0; x < n; ++x){
        a[x] = 0;
    }

    #pragma acc enter data copyin(has_equal[0:device_num_length][0:10])
    for (int x = 0; x < device_num_length; ++x){
        #pragma acc parallel
        {
            #pragma acc loop vector
            for (int y = 0; y < 10; ++y){
                has_equal[x][y] = 1;
            }
        }
    }
    #pragma acc exit data copyout(has_equal[0:device_num_length][0:10])


    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        device_num = x;
        for (int y = 0; y < device_num_length; ++y){
            for (int z = 0; z < 10; ++z){
                has_equal[y][z] = 0;
            }
        }
    }

    failed = failed + lengthless1;
  }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}