#ifndef T1
//T1:runtime,construct-independent,shutdown,V:2.5-2.7
int test1(){
    int err = 0;
    int is_present = 1;

    #pragma acc shutdown copy(is_present:1)
    is_present = 0;

    if (is_present == 1){
        err += 1;
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