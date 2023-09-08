#ifndef T1
//T1:known,declare,runtime,link,construct-independent,//
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * devdata, * devdata2, * hostdata;;

    devdata = (real_t *)acc_malloc(n * sizeof(real_t));
    devdata2 = (real_t *)acc_malloc(n * sizeof(real_t)));
    create_data(n, a);
    create_data(n, b);
    create_data(n, c);
    create_data(n, d);

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copy(devdata[0:n], devdata2[0:n]) copyout(d[0:n])
    {
        #pragma acc declare deviceptr(devdata)
        #pragma acc declare deviceptr(devdata2)
        #pragma acc link(devdata[0:n])
        #pragma acc link(devdata2[0:n])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < n; ++x) {
                    devdata[x] = a[x] + b[x];
                }
                #pragma acc loop
                for (int x = 0; x < n; ++x) {
                    devdata2[x] = c[x] + devdata[x];
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                d[x] += devdata2[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + b[x] + c[x]))) > PRECISION){
            err += 1;
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