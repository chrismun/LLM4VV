int test_shutdown(){
    int err = 0;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    #pragma acc data copyin(a[0:N]) copyout(b[0:N]) create(c[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i){
            b[i] = a[i];
            c[i] = a[i] + b[i];
        }

        #pragma acc shutdown_device
    }

    // Check that all values in c are equal to double the corresponding value in a
    for (int i = 0; i < N; ++i){
        if (c[i] != 2 * a[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;

    #pragma acc init

    int failed = test_shutdown();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    #pragma acc shutdown

    return failcode;
}