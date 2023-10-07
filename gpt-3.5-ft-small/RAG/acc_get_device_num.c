#ifndef T1
//T1:routine,private,V:2.5,S:2.0
int test1(){
    int err = 0, errors = 0;

    srand(SEED);
    int * a = (int *)malloc(10 * n * sizeof(int));
    int * b = (int *)malloc(10 * n * sizeof(int));
    int * c = (int *)malloc(10 * sizeof(int));
    int ** a_copy = (int **)malloc(10 * sizeof(int *));
    int ** b_copy = (int **)malloc(10 * sizeof(int *));
    int ** c_copy = (int **)malloc(10 * sizeof(int *));
    for (int x = 0; x < 10; ++x){
        a_copy[x] = (int *)malloc(n * sizeof(int));
        b_copy[x] = (int *)malloc(n * sizeof(int));
        c_copy[x] = (int *)malloc(sizeof(int));
        for (int y = 0; y < n; ++y){
            a_copy[x][y] = (int) (rand() / (real_t)(RAND_MAX / 10));
            b_copy[x][y] = (int) (rand() / (real_t)(RAND_MAX / 10));
            a[x * n + y] = a_copy[x][y];
            b[x * n + y] = b_copy[x][y];
        }
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop seq
            for (int x = 0; x < 10; ++x){
                c[x] = s_add(a + x * n, n) + v_add(b + x * n, a + x * n, n, x, 1);
            }
        }
    }


    for (int x = 0; x < 10; ++x){
        if (c[x] != s_add(a_copy[x], n) + v_add(b_copy[x], a_copy[x], n, x, 1)){
            errors = 1;
            break;
        }
    }

    #pragma acc exit data copyout(a[0:10*n], b[0:10*n], c[0:10])
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a_copy[x][y] = 0;
            b_copy[x][y] = 0;
        }
        c_copy[x][0] = 0;
    }

    acc_get_device_type privilege = acc_get_device_type();
    acc_set_device_type(acc_device_none);

    int *devicetarget_a = (int *) acc_pmalloc(10 * n * sizeof(int), privilege);
    int *devicetarget_b = (int *) acc_pmalloc(10 * n * sizeof(int), privilege);
    int *devicetarget_c = (int *) acc_pmalloc(10 * sizeof(int), privilege);
    int **devicetarget_a_copy = (int **) acc_pmalloc(10 * sizeof(int *), privilege);
    int **devicetarget_b_copy = (int **) acc_pmalloc(10 * sizeof(int *), privilege);
    int **devicetarget_c_copy = (int **) acc_pmalloc(10 * sizeof(int *), privilege);

    for (int x = 0; x < 10; ++x){
        devicetarget_a_copy[x] = (int *) acc_pmalloc(n * sizeof(int), privilege);
        devicetarget_b_copy[x] = (int *) acc_pmalloc(n * sizeof(int), privilege);
        devicetarget_c_copy[x] = (int *) acc_pmalloc(sizeof(int), privilege);
        for (int y = 0; y < n; ++y){
            devicetarget_a_copy[x][y] = a_copy[x][y];
            acc_copyin(&(devicetarget_a[x * n + y]), &(a_copy[x][y]), sizeof(int));
            devicetarget_b_copy[x][y] = b_copy[x][y];
            acc_copyin(&(devicetarget_b[x * n + y]), &(b_copy[x][y]), sizeof(int));
        }
        devicetarget_c_copy[x][0] = c_copy[x][0];
        acc_copyin(&(devicetarget_c[x]), &(c_copy[x][0]), sizeof(int));
    }

    #pragma acc data  present(devicetarget_a[0:10*n], devicetarget_b[0:10*n]) present(devicetarget_c[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop seq
            for (int x = 0; x < 10; ++x){
                devicetarget_c[x] = s_add(devicetarget_a + x * n, n) + v_add(devicetarget_b + x * n, devicetarget_a + x * n, n, x, 1);
            }
        }
    }
    #pragma acc exit data copyout(devicetarget_a[0:10*n], devicetarget_b[0:10*n], devicetarget_c[0:10])

    for (int x = 0; x < 10; ++x){
        if (c_copy[x][0] != devicetarget_c[x]){
            errors = 1;
            break;
        }
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (a_copy[x][y] != devicetarget_a_copy[x][y]){
                errors = 1;
                break;
            }
            if (b_copy[x][y] != devicetarget_b_copy[x][y]){
                errors = 1;
                break;
            }
        }
        if (c_copy[x][0] != devicetarget_c_copy[x][0]){
            errors = 1;
            break;
        }
    }

    if (errors == 1){
        for (int x = 0; x < 10; ++x){
            if (c[x] != s_add(a_copy[x], n) + v_add(b_copy[x], a_copy[x], n, x, 1)){
                err = 1;
                break;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a_copy[x][y] = 0;
            b_copy[x][y] = 0;
        }
        c_copy[x][0] = 0;
    }

    if (err == 1){
        err = 0;
        for (int x = 0; x < 10; ++x){
            if (c_copy[x][0] != 0){
                err = 1;
                break;
            }
            for (int y = 0; y < n; ++y){
                if (a_copy[x][y] != 0){
                    err = 1;
                    break;
                }
                if (b_copy[x][y] != 0){
                    err = 1;
                    break;
                }
            }
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