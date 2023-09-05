#ifndef T1
//T1:declare,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    char a = 123, b = 0;
    #pragma acc enter data copyin(a)
    #pragma acc declare copyin(b)
    {
        #pragma acc data present(a, b)
        {
            #pragma acc parallel present(a, b)
            {
                b = a + 1;
            }
        }
    }
    #pragma acc exit data delete(a) copyout(b)
    if (b != 124){
        err += 1;
        fprintf(stderr, "Error1: %d\n", b);
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