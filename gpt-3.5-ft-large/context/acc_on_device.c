#ifndef T1
//T1:runtime,devonly,internal-control-values,syntactic,V:2.5-3.2
int test1(){
    int err = 0;
    if (acc_on_device(acc_get_device_type()) == acc_get_device_type()){
        return err;
    }
    else{
        return 1;
    }
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