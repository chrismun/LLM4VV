#ifndef T1
//T1:loop,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int i = 0, a = 0;
    #pragma acc data copyin(a) copyout(a)
    {
        a = 3;
        #pragma acc parallel
        {
            #pragma acc loop private(i)
            for (i = 0; i < 100; ++i){
                a = 3;
            }
        }
    }
    return err;
}
#endif

#ifndef T2
//T2:loop,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    int i = 0, a = 0;
    #pragma acc data copyin(a) copyout(a)
    {
        a = 3;
        #pragma acc parallel num_gangs(100) num_workers(1) vector_length(1)
        {
            #pragma acc loop private(i)
            for (i = 0; i < 100; ++i){
                a = a + 1;
            }
        }
    }
    if (a != 103){
        err += 1;
    }
    return err;
}
#endif

#ifndef T3
//T3:loop,V:2.0-2.7
int test3(){
    int err = 0;
    int i = 0, a[1000];
    for (int x = 0; x < 1000; ++x){
        a[x] = 0;
    }
    #pragma acc data copyin(a[0:1000])
    {
        #pragma acc parallel
        {
            #pragma acc loop private(i)
            for (i = 0; i < 1000; ++i){
                a[i] = 3;
            }
        }
    }
    for (int x = 0; x < 1000; ++x){
        if (a[x] != 3){
            ++err;
        }
    }
    return err;
}
#endif

#ifndef T4
//T4:loop,V:2.0-2.7
int test4(){
    int err = 0;
    int i = 0, a[1000];
    for (int x = 0; x < 1000; ++x){
        a[x] = 0;
    }
    #pragma acc data copyin(a[0:1000])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (i = 0; i < 1000; ++i){
                a[i] = 3;
            }
        }
    }
    for (int x = 0; x < 1000; ++x){
        if (a[x] != 3){
            ++err;
        }
    }
    return err;
}
#endif

#ifndef T5
//T5:loop,V:2.0-2.7
int test5(){
    int err = 0;
    int i = 0, a[10][10];
    for (int y = 0; y < 10; ++y){
        for (int x = 0; x < 10; ++x){
            a[y][x] = 0;
        }
    }
    #pragma acc data copyin(a[0:10][0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop private(i)
            for (int y = 0; y < 10; ++y){
                for (i = 0; i < 10; ++i){
                    a[y][i] = 3;
                }
            }
        }
    }
    for (int y = 0; y < 10; ++y){
        for (int x = 0; x < 10; ++x){
            if (a[y][x] != 3){
                ++err;
            }
        }
    }
    return err;
}
#endif

#ifndef T6
//T6:loop,V:2.0-2.7
int test6(){
    int err = 0;
    int i = 0, a[10][10];
    for (int y = 0; y < 10; ++y){
        for (int x = 0; x < 10; ++x){
            a[y][x] = 0;
        }
    }
    #pragma acc data copyin(a[0:10][0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int y = 0; y < 10; ++y){
                for (i = 0; i < 10; ++i){
                    a[y][i] = 3;
                }
            }
        }
    }
    for (int y = 0; y < 10; ++y){
        for (int x = 0; x < 10; ++x){
            if (a[y][x] != 3){
                ++err;
            }
        }
    }
    return err;
}
#endif

#ifndef T7
//T7:loop,V:2.0-2.7
int test7(){
    int err = 0;
    int i = 0, a[10][10][10];
    for (int z = 0; z < 10; ++z){
        for (int y = 0; y < 10; ++y){
            for (int x = 0; x < 10; ++x){
                a[z][y][x] = 0;
            }
        }
    }
    #pragma acc data copyin(a[0:10][0:10][0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int z = 0; z < 10; ++z){
                for (int y = 0; y < 10; ++y){
                    for (i = 0; i < 10; ++i){
                        a[z][y][i] = 3;
                    }
                }
            }
        }
    }
    for (int z = 0; z < 10; ++z){
        for (int y = 0; y < 10; ++y){
            for (int x = 0; x < 10; ++x){
                if (a[z][y][x] != 3){
                    ++err;
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
#ifdef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
#ifdef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifdef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
#ifdef T4
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test4();
    }
    if (failed != 0){
        failcode = failcode + (1 << 3);
    }
#endif
#ifdef T5
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test5();
    }
    if (failed != 0){
        failcode = failcode + (1 << 4);
    }
#endif
#ifdef T6
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test6();
    }
    if (failed != 0){
        failcode = failcode + (1 << 5);
    }
#endif
#ifdef T7
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test7();
    }
    if (failed != 0){
        failcode = failcode + (1 << 6);
    }
#endif
    return failcode;
}