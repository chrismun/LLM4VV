#ifndef T2
//T2:parallel,default_present,default_none,combined-constructs,C99,C11
int test2(){
    int err = 0;
    srand(SEED);

    int a = 0;
    int b = 0;

    #pragma acc parallel
    {
        a = 1;  // Exposed access to 'a'
    }

    #pragma acc parallel default(none) present(a) private(b)
    {
        b = a;  // Exposed access to 'a'
    }

    if (b != 1){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
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