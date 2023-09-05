#ifndef T2
//T2:parallel,loop,data,V:2.7-2.*,I:compiler-team,N:2,C:collapse
int test2(){
    int err = 0;
    srand(SEED);

    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % 10;
        b[x] = 0;
    }

    #pragma acc parallel loop collapse(2) copyout(b[0:n])
    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            b[x] += a[y];
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != a[x] * n){
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