#ifndef T1
//T1:detach,syntactic,V:2.0-2.7
int test1(){
    int err = 0;
    int* a = (int *)malloc(n * sizeof(int));
    int *results = (int *)malloc(n * sizeof(int));
    real_t false_margin = pow(exp(1), log(.5)/n);

    for (int x = 0; x < n; ++x){
        results[x] = 2;
        a[x] = rand() % 10 + 1;
    }

    for (int x = 1; x < n; ++x)
        results[x] = results[x-1] * 2;

    #pragma acc data copyin(a[0:n])
    for (int x = 0; x < n; ++x){
        #pragma acc enter data copyin(results[x:1])
    }


    for (int x = 0; x < n; ++x){
        #pragma acc parallel present(results[x:1])
        {
            int current = 2;
            for (int y = 1; y <= a[x]; ++y){
                results[x] = (current *= 2);
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(results[x] - pow(2, a[x])) > false_margin * pow(2, a[x])){
            err += 1;
            break;
        }
    }

    for (int x = 0; x < n; ++x){
        #pragma acc exit data delete(results[x:1])
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    init_test();
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    revert_test();
#endif
    return failcode;
}