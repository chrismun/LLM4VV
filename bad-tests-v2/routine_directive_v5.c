int test(){
    int err = 0;

    #pragma acc routine(gang)
    void compute(int* a, int* b, int n){
        #pragma acc loop gang
        for (int i = 0; i < n; ++i){
            b[i] = a[i] + 1;
        }
    }

    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc routine(compute)
    compute(a, b, n);

    for (int i = 0; i < n; ++i){
        if (b[i] != a[i] + 1){
            err += 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    failcode = test();
    return failcode;
}