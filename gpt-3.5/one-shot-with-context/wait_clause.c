#ifndef T1
//T1:wait_test:data,wait,present,V:2.0-3.0
int test1(){
    int a = 0;
    int err = 0;

    #pragma acc data copy(a)
    {
        #pragma acc host_data use_device(a)
        {
            a = 1;
            #pragma acc parallel wait(a)
            {
                a = 2;
            }
            if (a != 2){
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