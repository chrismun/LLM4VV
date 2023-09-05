#ifndef T1
//T1:declare,data,executable-data,pragma,partitioning,construct-independent,V:2.0-3.1
int test1(){
    int err = 0;
    int dev = acc_get_device_num(acc_get_device_type());
    if (dev < 0){
        return 1;
    }
    int * ptr = (int *)malloc(10 * sizeof(int));
    int * ptr1 = (int *)malloc(10 * sizeof(int));
    int * tst = (int *)malloc(10 * sizeof(int));
    int * tst1 = (int *)malloc(10 * sizeof(int));
    unsigned int i;

#pragma acc declare create(ptr[0:10], ptr1[0:10])
    {
#pragma acc parallel loop
        for (i = 0; i < 10; ++i){
            ptr[i] = i;
        }
#pragma acc parallel loop
        for (i = 0; i < 10; ++i){
            ptr1[i] = i;
        }
    }

#pragma acc parallel present(ptr[:10], ptr1[:10], tst[:10], tst1[:10])
    {
#pragma acc loop
        for (i = 0; i < 10; ++i){
            tst[i] = ptr[i] + ptr1[i];
        }
    }
    for (i = 0; i < 10; ++i){
        if (tst[i] != ptr[i] + ptr1[i]){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:declare,data,executable-data,pragma,construct-independent,V:2.0-3.1
int test2(){
    int err = 0;
    int dev = acc_get_device_num(acc_get_device_type());
    if (dev < 0){
        return 1;
    }
    int * ptr = (int *)malloc(10 * sizeof(int));
    int * tst = (int *)malloc(10 * sizeof(int));
    unsigned int i;

#pragma acc enter data copyin(ptr[0:10])
#pragma acc declare create(ptr[0:10])
    {
#pragma acc parallel loop
        for (i = 0; i < 10; ++i){
            ptr[i] = i;
        }
    }
#pragma acc parallel present(ptr[:10], tst[:10])
    {
#pragma acc loop
        for (i = 0; i < 10; ++i){
            tst[i] = ptr[i];
        }
    }
    for (i = 0; i < 10; ++i){
        if (tst[i] != i){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:declare,data,executable-data,pragma,construct-independent,V:2.0-3.1
int test3(){
    int err = 0;
    int dev = acc_get_device_num(acc_get_device_type());
    if (dev < 0){
        return 1;
    }
    int * ptr = (int *)malloc(10 * sizeof(int));
    int * tst = (int *)malloc(10 * sizeof(int));
    unsigned int i;

#pragma acc enter data copyin(ptr[0:10])
#pragma acc declare create(ptr[0:10])
#pragma acc parallel present(ptr[:10], tst[:10])
    {
#pragma acc loop
        for (i = 0; i < 10; ++i){
            tst[i] = ptr[i];
        }
    }
    for (i = 0; i < 10; ++i){
        if (tst[i] != i){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:declare,data,executable-data,pragma,partitioning,construct-independent,V:2.0-3.1
int test4(){
    int err = 0;
    int dev = acc_get_device_num(acc_get_device_type());
    if (dev < 0){
        return 1;
    }
    int * ptr = (int *)malloc(10 * sizeof(int));
    int * ptr1 = (int *)malloc(10 * sizeof(int));
    int * tst = (int *)malloc(10 * sizeof(int));
    int * tst1 = (int *)malloc(10 * sizeof(int));
    unsigned int i;

#pragma acc declare create(ptr[0:10])
    {
#pragma acc parallel loop
        for (i = 0; i < 10; ++i){
            ptr[i] = i;
        }
    }

#pragma acc declare create(ptr1[0:10])
    {
#pragma acc parallel loop
        for (i = 0; i < 10; ++i){
            ptr1[i] = 10 - i;
        }
    }

#pragma acc parallel present(ptr[0:10], ptr1[0:10], tst[0:10], tst1[0:10])
    {
#pragma acc loop
        for (i = 0; i < 10; ++i){
            tst[i] = ptr[i] + ptr1[i];
        }
    }
    for (i = 0; i < 10; ++i){
        if (tst[i] != 10){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T5
///T5:declare,data,executable-data,pragma,construct-independent,V:2.0-3.1
int test5(){
    int err = 0;
    int dev = acc_get_device_num(acc_get_device_type());
    if (dev < 0){
        return 1;
    }
    int * ptr;
    int * tst = (int *)malloc(10 * sizeof(int));
    unsigned int i;

    if (dev == acc_get_num_devices(acc_device_xeonphi)){
        ptr = (int *)malloc(10 * sizeof(int));
    }

    if (dev == acc_get_device_type()){
#pragma acc enter data copyin(ptr[0:10])
    }

#pragma acc declare create(ptr[0:10])
    if (dev == acc_get_num_devices(acc_device_xeonphi)){
        for (i = 0; i < 10; ++i){
            ptr[i] = i;
        }
    }

#pragma acc parallel present(ptr[0:10], tst[0:10])
    {
#pragma acc loop
        for (i = 0; i < 10; ++i){
            tst[i] = ptr[i];
        }
    }
    for (i = 0; i < 10; ++i){
        if (tst[i] != i){
            err = 1;
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
#ifndef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
    return failcode;
}