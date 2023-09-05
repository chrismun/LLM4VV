#ifndef T1
//T1:parallel,loop,loopconstruct,auto,V:1.0-2.5
int test1(){
    int err = 0;
    srand(SEED);
    real_t* a = (real_t *)malloc(n * sizeof(real_t));
    real_t* b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 10.0;
        b[x] = 0.0;
    }

    #pragma acc parallel loop auto
    for (int x = 0; x < n; ++x){
        b[x] = a[x];
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
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