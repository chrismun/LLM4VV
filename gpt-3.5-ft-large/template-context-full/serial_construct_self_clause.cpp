#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copyin(present_vector[0:LENGTH], original_vector[0:LENGTH]) create(self_vector[0:LENGTH])
    {
        #pragma acc serial loop self(self_vector[0:LENGTH])
        for (int x = 0; x < LENGTH; ++x){
              self_vector[x] = 0.0f;
        }

        for (int x = 0; x < LENGTH; ++x){
            self_vector[x] += original_vector[x];
            for (int y = 0; y < LENGTH; ++y){
                if (x != y)
                    self_vector[x] -= self_vector[x] * ((float) (ITERATIONS/2) / (self_vector[x] + (self_vector[x] - present_vector[x])));

            }
            present_vector[x] = self_vector[x] * 2 + 1;
        }

        for (int x = 0; x < LENGTH; ++x){
            if (fabs(present_vector[x] - (self_vector[x] * 2 + 1)) > PRECISION){
                err += 1;
            }
        }
    }

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