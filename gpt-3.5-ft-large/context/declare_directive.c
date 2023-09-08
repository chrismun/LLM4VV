#ifndef T1
//T1:declare,pragma,V:2.0-2.7
int test1(){
    int err = 0;
    int multipr = 1;
    real_t err_t1 = 0;

    int temp = n;
    #pragma acc declare copyin(temp)
    n = (int)((n - 2)/3);
    #pragma acc loop reduction(*:multipr)
    for (int x = 0; x < temp; ++x){
        multipr *= 3;
    }
    for (int x = 1; x < temp/3; ++x){
        err_t1 += multipr;
    }
    if (err_t1 > PRECISION){
        err += 1;
        printf("%f", err_t1);
    }
    n = temp;

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