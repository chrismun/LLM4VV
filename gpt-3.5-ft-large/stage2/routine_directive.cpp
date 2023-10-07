#include "acc_testsuite.h"
#ifndef T1
//T1:routine directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    //debug info 
    #pragma acc routine seq 
    void seq_func(int a);

    int temp = 0;
    int multi = 1; 
    int temp_error = 0;

    #pragma acc routine seq  
    int Acc_seq_func(int a){
        #pragma acc loop seq
       // translation_unit_contains: acc routine seq
        for (int x = 0; x < a; ++x){
            temp = (int) ((float) SEED / RAND_MAX * (a + 1)) - 1;
            //Test for set device_num & host_data
            multi = multi * temp;
        }
        return multi;
    }

    for (int x = 0; x < SEED; ++x){
        temp_error = temp_error + (1 + (x * x));
    }

    seq_func(SEED);

    if (multi == temp_error){
        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2: routine directive,V:2.7-3.3
int test2(){
    int err = 0;
    srand(SEED);
    
    int temp = 0;
    int multi_temp = 0; 
    int temp_error = 0;

     void local_func(int a,int *multi);
    #pragma acc routine worker
    void worker_func(int a,int *multi);
    void local_func_upload(int*temp, int length);
       
    local_func_upload(&temp,length); 
    }
    #pragma acc routine local_func_bind(local_func)
    void worker_func_upload(int*temp,int length){
        #pragma acc loop worker
        for( int i=0; i<length; i++)
        {
            local_func(temp[i],&multi_temp);
        }
    }
    #pragma acc routine 
    void local_func(int a,int *multi){
        *multi = *multi * a; 
    }
   int main() {
        #pragma acc data copyin(temp[0:length])
        worker_func_upload(namE1,namE2);
        #pragma acc data copyin(temp[0:length])
        worker_func_upload(namE2,namE2);
    }

    for (int x = 0; x < SEED; ++x){
        temp_error = temp_error + (1 + (x * x));
    }

    if (abs(temp_error - multi_temp) > 2 * SEED){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}