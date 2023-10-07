#ifndef T1
//T1:data,data-region,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    int * data = (int *)malloc(10 * sizeof(int));
    int device_copy, found;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        data[x] = 0;
        for (int y = 0; y < n; ++y){
            data[x] = data[x] + (a[x * n + y] > 5.0);
        }
    }

    #pragma acc data copy(data[0:10]) copyin(a[0:10*n])
    {
        #pragma acc parallel
        {
            int private_data = 0;
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    private_data = private_data + (a[x * n + y] > 5.0);
                }
            }
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                data[x] = data[x] + private_data;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        device_copy = 0;
        for (int y = 0; y < n; ++y){
            device_copy = device_copy + (a[x * n + y] > 5.0);
        }
        found = 0;
        for (int y = 0; y <= x; ++y){
            if (device_copy == data[y]){
                found = 1;
                break;
            }
        }
        if (found == 0){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:data,data-region,construct-independent,reference-pointers,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    int * ptr, poneA;
    int * data = (int *)malloc(10 * sizeof(int));
    int * is_present = (int *)malloc(10 * sizeof(int));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    for (int x = 0; x < 10; ++x){
        data[x] = 0;
        for (int y = 0; y < x+1; ++y){
            data[x] = data[x] + (a[y] > 5);
        }
    }

    #pragma acc data copy(data[0:10]) present_or_copyin(is_present[0:10])
    {
        #pragma acc parallel
        {
            real_t private_data = 0;
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                real_t temp = 0;
                for (int y = 0; y < x+1; ++y){
                    temp = temp + a[y];
                }
                if (temp > 5){
                    is_present[x] = 1;
                }
                else{
                    is_present[x] = 0;
                }
            }
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                private_data = 0;
                poneA = -10;
                for (int y = 0; y < x+1; ++y){
                    poneA = poneA + is_present[y] * (poneA == -10);
                    private_data = private_data + a[poneA + y];
                }
                data[x] = data[x] + private_data;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        real_t temp = 0;
        for (int y = 0; y < x+1; ++y){
            temp = temp + a[y];
        }
        if (temp > 5){
            is_present[x] = 1;
        }
        else{
            is_present[x] = 0;
        }
    }
    for (int x = 0; x < 10; ++x){
        real_t temp = 0;
        poneA = -10;
        for (int y = 0; y < x+1; ++y){
            poneA = poneA + is_present[y] * (poneA == -10);
            temp = temp + a[poneA + y];
        }
        if (data[x] != (int)temp){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:data,data-region,enter-data,LOOP-STRUCTURE,PASS
int test3(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(10 * n * sizeof(int));
    int written;
    int * counted_data = (int *)malloc(10 * sizeof(int));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0;
    }

    #pragma acc data copy(a[0:10*n])
    {
        #pragma acc enter data create(a[0:10*n])
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10 * n; ++x){
                ++a[x];
            }
        }
    }
    for (int x = 0; x < 10 * n; ++x){
        if (a[x] != 1){
            err += 1;
            break;
        }
    }
    #pragma acc data present(a[0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                written = 0;
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    if (a[x * n + y] != 1){
                        #pragma acc atomic
                        written = 1;
                    }
                }
                counted_data[x] = written;
            }
        }
    }
    for (int x = 0; x < 10; ++x){
        written = 0;
        for (int y = 0; y < n; ++y){
            if (a[x * n + y] != 1){
                written = 1;
            }
        }
        if (counted_data[x] != written){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:data,data-region,enter-data,construct-independent,LOOP-CONTINUE,PASS
int test4(){
    int err = 0;
    srand(SEED);

    int pcopy[10];
    int seq, found;

    for (int x = 0; x < 10; ++x){
        /* Random number in range [0, n - 1] */
        pcopy[x] = rand() % n;
    }

    #pragma acc data copyin(pcopy[0:10])
    {
        #pragma acc parallel
        {
            for (int x = 0; x < 10; ++x){
                seq = 0;
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    if (y == pcopy[x]){
                        seq = 1;
                        #pragma acc continue
                    }
                    #pragma acc atomic
                        a[x] += seq;
                }
            }
        }
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            found = 0;
            if (y == pcopy[x]){
                found = 1;
            }
            if (found == 0){
                if (a[x] != y + 1){
                    err += 1;
                }
            }
            else{
                if (a[x] != n * (n - 1) / 2){
                    err += 1;
                }
            }
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:data,data-region,enter-data,construct-independent,reference-pointers,LOOP-CONTINUE,PASS
int test5(){
    int err = 0;
    srand(SEED);

    int pcopy[10];
    int * a = (int *)malloc(10 * n * sizeof(int));
    int * ptr, psum;
    int seq, present;

    for (int x = 0; x < 10; ++x){
        pcopy[x] = rand() % n + 1;
    }

    #pragma acc data copyin(pcopy[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                seq = 0;
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    if (y == pcopy[x]){
                        seq = 1;
                        #pragma acc continue
                    }
                    a[x * n + y] = y + 1;
                }
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        seq = 0;
        for (int y = 0; y < n; ++y){
            if (y == pcopy[x]){
                seq = 1;
            }
            if (seq == 0){
                if (a[x * n + y] != y + 1){
                    err += 1;
                }
            }
            else{
                present = 0;
                psum = 0;
                for (int z = 0; z < n; ++z){
                    present = present || (z == pcopy[x]);
                    psum += z * (z == pcopy[x]);
                }
                if (present == 1){
                    if (a[x * n + y] != psum){
                        err += 1;
                    }
                }
                else{
                    if (a[x * n + y] != y + 1){
                        err += 1;
                    }
                }
            }
        }
    }

    return err;
}
#endif

#ifndef T6
//T6:data,data-region,enter-data,construct-independent,reference-pointers,SIMD,LOOP-CONTINUE,PASS
int test6(){
    int err = 0;

    int * bcopy = (int *)malloc(10 * sizeof(int));
    int ** a = (int **)malloc(10 * sizeof(int *));
    int * ptr;

    for (int x = 0; x < 10; ++x){
        a[x] = (int *)malloc(10 * x * sizeof(int));
    }

    int ** acopy = (int **)malloc(10 * sizeof(int *));
    for (int x = 0; x < 10; ++x){
        acopy[x] = (int *)malloc(10 * x * sizeof(int));
    }

    for (int x = 0; x < 10; ++x){
        bcopy[x] = rand() % n + 1;
    }
    #pragma acc enter data copyin(bcopy[0:10])
    #pragma acc enter data copyin(acopy[0:10][0:10*n])

    for (int x = 0; x < 10; ++x){
        a[x] = &(acopy[x][0]);
    }

    #pragma acc data present(bcopy[0:10]) present(acopy[0:10][0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                #pragma acc loop
                for (int y = 0; y < x; ++y){
                    a[x][y] = x*y+1;
                }
                #pragma acc loop
                for (int y = x; y < n; ++y){
                    a[x][y] = 0;
                }
            }

            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                bcopy[x] = bcopy[x] % x + 1;
                int seq = 0;
                #pragma acc loop vector
                for (int y = 0; y < n; ++y){
                    if (y == bcopy[x]){
                        seq = 1;
                    }
                    #pragma acc atomic
                    a[x][y] += seq;
                }
            }
        }
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < x; ++y){
            if (a[x][y] != y+2){
                err += 1;
            }
        }
        for (int y = x; y < n; ++y){
            if (a[x][y] != 0){
                err += 1;
            }
        }
    }

    return err;
}
#endif

#ifndef T7
//T7:data,data-region,enter-data,create,PASS
int test7(){
    int host = 1;
    int err = 0;
    int * a = (int *)malloc(10 * n * sizeof(int));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0;
    }

    #pragma acc enter data create(a[0:10*n])
    for (int x = 0; x < 10 * n; ++x){
        if (a[x] != host){
            err += 1;
        }
    }
    #pragma acc exit data delete(a[0:10*n])
    for (int x = 0; x < 10 * n; ++x){
        a[x] = host;
    }
    #pragma acc enter data copyin(a[0:10*n])
    for (int x = 0; x < 10 * n; ++x){
        if (a[x] != host){
            err += 1;
        }
    }

    return err;
}
#endif

#ifndef T8
//T8:data,data-region,exit-data,LOOP-VARIABLE-PARALLELISM,PASS
int test8(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    int * exp = (int *)malloc(10 * sizeof(int));

    for (int x = 0; x < 10; ++x){
        exp[x] = 0;
        for (int y = 0; y < n; ++y){
            a[y] = rand() / (real_t)(RAND_MAX / 10);
            exp[x] = exp[x] + (a[y] > 5);
        }
        exp[x] += 1;
    }

    #pragma acc data copyin(a[0:n]) create(exp[0:10])
    for (int x = 0; x < 10; ++x){
        int items = 1;
        #pragma acc parallel private(items)
        {
            items = 0;
            #pragma acc loop
            for (int y = 0; y < n; ++y){
                if (a[y] > 5){
                    #pragma acc atomic
                        items += 1;
                }
            }
            #pragma acc loop
            for (int y = 0; y < x; ++y){
                if (exp[y] == items){
                    #pragma acc atomic
                        exp[y] += 1;
                }
            }
        }
    }
    for (int x = 0; x < 10; ++x){
        if (exp[x] != 1){
            err += 1;
        }
    }

    return err;
}