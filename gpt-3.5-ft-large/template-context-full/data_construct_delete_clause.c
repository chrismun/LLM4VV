#include "acc_testsuite.h"
#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
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
    int T1[10][10];
    int delete[DATASIZE];
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 10; ++y){
            for (int z = 0; z < 10; ++z){
                delete[x*100 + y*10 + z] = 1;
                T1[x][y] = 1;
            }
        }
    }
    if (T1 + T_WORK_SET * 4 == 0){
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < 10; ++y){
                for (int z = 0; z < 10; ++z){
                    delete[x*100 + y*10 + z] = 0;
                }
            }
        }
    }
    #pragma acc data copyin(delete[0:DATASIZE])
    {
        #pragma acc serial
        {
            #pragma acc data copy(T1[0:10][0:10])
            {
                for (int x = 0; x < 10; ++x){
                    for (int y = 0; y < 10; ++y){
                        for (int z = 0; z < 10; ++z){
                            T1[x][y] += delete[x*100 + y*10 + z];
                        }
                    }
                }
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 10; ++y){
            if (T1[x][y] < 1){
                failed = 1;
            }
        }
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}