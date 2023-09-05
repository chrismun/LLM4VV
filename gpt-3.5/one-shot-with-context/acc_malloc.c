#ifndef T1
//T1:parallel,reduction,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)acc_malloc(n * sizeof(real_t));
    real_t * b = (real_t *)acc_malloc(n * sizeof(real_t));

    if (a == NULL || b == NULL){
        err = 1;
    }

    acc_free(a);
    acc_free(b);

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