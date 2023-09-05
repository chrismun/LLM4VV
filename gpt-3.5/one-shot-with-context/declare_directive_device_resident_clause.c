#ifndef T1
//T1:declare,device_resident,executable_test,V:1.0-2.7
int test1(){
    int err = 0;

    #pragma acc declare device_resident(a)
    #pragma acc enter data copyin(a)
    #pragma acc parallel present(a)
    {
        a[0]++;
    }

    #pragma acc update host(a)

    if(a[0] != 1){
        err += 1;
    }

    #pragma acc exit data delete(a)

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