#ifndef T1
//T1:init,devonly-no-construct-clause,default-present,device-neutral-no-default
int test1(){
    int err = 0;
    if (acc_get_device_type() != acc_device_none){
        #pragma acc init
        {
            #pragma acc enter data copyin(arr[0:10])
            #pragma acc parallel present(arr[0:10])
            {
                int host_err = 0;
                for (int x = 0; x < 10; ++x){
                    if (arr[x] != 0){
                        #pragma omp atomic
                        ++host_err;
                    }
                }
                if (host_err != 0){
                    #pragma omp atomic
                    ++err;
                }
            }
            #pragma acc exit data delete(arr[0:10])
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