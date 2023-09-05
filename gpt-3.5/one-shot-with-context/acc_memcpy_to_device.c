#ifndef T1
//T1:devices,runtime,data,data-region,V:2.7-3.0
int test1(){
    int i, err = 0;

    #pragma acc enter data copyin(i)

    i = 5;

    #pragma acc parallel present(i)
    {
        i += 1;
    }

    #pragma acc exit data copyout(i)

    if (i != 6){
        err += 1;
    }

    return err;
}

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