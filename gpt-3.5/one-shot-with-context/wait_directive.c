#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;

    int n = 100;
    int *arr = (int *)malloc(n * sizeof(int));

    #pragma acc data copy(arr[0:n])
    {
        #pragma acc parallel
        {
            for (int i = 0; i < n; ++i) {
                arr[i] = i;
            }

            #pragma acc wait
        }

        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i) {
                arr[i] *= 2;
            }

            #pragma acc wait
        }
    }

    for (int i = 0; i < n; ++i) {
        if (arr[i] != i * 2) {
            err += 1;
            break;
        }
    }

    free(arr);

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