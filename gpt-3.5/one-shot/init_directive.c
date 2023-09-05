#ifndef T1
//T1:init
int test1(){
    int err = 0;
    real_t x = 10.0;
    real_t y;

    #pragma acc parallel loop init(x)
    for (int i = 0; i < n; ++i){
        y = x;
    }

    if (y != 10.0){
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

    return failcode;
}