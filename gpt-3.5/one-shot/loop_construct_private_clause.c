#ifndef T1
//T1:parallel,data,data-region,V:2.7-9.0
int test1(){
    int err = 0;
    int x = 0;
    int y = 0;

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for (x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
    }

    #pragma acc parallel loop private(y) copyout(b[0:n])
    for (x = 0; x < n; ++x){
        y = 2 * x;
        a[x] = y;
        b[x] = a[x];
    }

    for (x = 0; x < n; ++x){
        if (b[x] != 2 * x){
            err += 1;
            break;
        }
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