#ifndef T1
//T1:parallel,firstprivate,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));
    int * d = (int *)malloc(n * sizeof(int));
    int * has_visited = (int *)malloc(n/10 * sizeof(int));
    int total_visited = 0;
    int * passed_a = (int *)malloc(10 * sizeof(int));
    int * passed_b = (int *)malloc(10 * sizeof(int));
    int num_in_set;
    int temp;

    for (int x = 0; x < n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 1;
        d[x] = 1;
    }
    for (int x = 0; x < n/10; ++x){
        has_visited[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        while (1){
            temp = rand() % (n/10);
            if (has_visited[temp] == 0){
                has_visited[temp] = 1;
                break;
            }
        }
        for (int y = 0; y < 8; ++y){
            a[x] += 1<<y;
        }
        b[x] = temp;
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copyout(d[0:n])
    {
        #pragma acc parallel firstprivate(c[0:n])
        {
            #pragma acc loop gang independent
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + 1;
            }
            #pragma acc loop worker independent
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + 1;
            }
            #pragma acc loop vector independent
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + 1;
            }
            #pragma acc loop seq independent
            for (int x = 0; x < n; ++x){
                c[x] = c[x] + 1;
            }
            #pragma acc loop gang worker vector seq independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x]/2;
            }
            #pragma acc loop worker vector seq gang independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x]/2;
            }
            #pragma acc loop vector seq gang worker independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x]/2;
            }
            #pragma acc loop seq gang worker vector independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x]/2;
            }
            #pragma acc loop parallel
            for (int x = 0; x < n; ++x){
                d[x] = c[x] + a[x];
            }
        }
    }
    for (int x = 0; x < n; ++x){
        if (7 > d[x] || d[x] > 8){
            err += 1;
            break;
        }
    }

    for (int x = 0; x < n; ++x){
        has_visited[b[x]] = 0;
    }
    for (int x = 0; x < n; ++x){
        if (has_visited[x] != 0){
            err = err + 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:parallel,firstprivate,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));
    int * c = (int *)malloc(n * sizeof(int));
    int * d = (int *)malloc(n * sizeof(int));
    int * has_visited = (int *)malloc(n/10 * sizeof(int));
    int total_visited = 0;
    int * passed_a = (int *)malloc(10 * sizeof(int));
    int * passed_c = (int *)malloc(10 * sizeof(int));
    int num_in_set;
    int temp;

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 0;
    }

    for (int x = 0; x < n/10; ++x){
        has_visited[x] = 0;
    }

    for (int x = 0; x < n; ++x){
        while (1){
            temp = rand() % (n/10);
            if (has_visited[temp] == 0){
                has_visited[temp] = 1;
                break;
            }
        }
        b[x] = temp;
    }

    #pragma acc data copyin(a[0:n]) copyin(b[0:n]) copyout(d[0:n])
    {
        #pragma acc parallel firstprivate(a[0:n], b[0:n])
        {
            #pragma acc loop gang independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
            #pragma acc loop worker independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
            #pragma acc loop vector independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
            #pragma acc loop seq independent
            for (int x = 0; x < n; ++x){
                a[x] = a[x] * 2;
            }
            #pragma acc loop gang worker vector seq independent
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (d[x] - (2 * a[x]) != b[x]){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:parallel,firstprivate,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(10 * n * sizeof(int));
    int * b = (int *)malloc(10 * n * sizeof(int));
    int * c = (int *)malloc(10 * n * sizeof(int));
    int * has_visited = (int *)malloc(10 * n/10 * sizeof(int));
    int total_visited = 0;
    int * passed_a = (int *)malloc(10 * 10 * sizeof(int));
    int * passed_c = (int *)malloc(10 * 10 * sizeof(int));
    int num_in_set;
    int temp;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 1;
    }
    for (int x = 0; x < n/10; ++x){
        has_visited[x] = 0;
    }

    for (int x = 0; x < 10 * n; ++x){
        while (1){
            temp = rand() % (n/10);
            if (temp == n/20) {
                break;
            }
            if (has_visited[temp] == 0) {
                has_visited[temp] = 1;
                break;
            }
        }
        b[x] = 1;
        for (int y = 0; y < 8; ++y) {
            a[x] += 1<<y;
        }
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10*n])
    {
        #pragma acc parallel firstprivate(c)
        {
            #pragma acc loop gang independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            #pragma acc loop worker independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            #pragma acc loop vector independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            #pragma acc loop seq independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            for (int x = 0; x < n/10; ++x) {
                has_visited[x] = 0;
            }
            #pragma acc loop gang worker vector seq independent
            for (int x = 0; x < 10 * n; ++x) {
                if (b[x] == 1) {
                    temp = a[x];
                    while (temp > 1) {
                        temp = temp / 2;
                        c[x] = c[x] * 2;
                    }
                }
            }
            #pragma acc loop worker vector seq gang independent
            for (int x = 0; x < 10 * n; ++x) {
                if (b[x] == 1) {
                    temp = a[x];
                    while (temp > 1) {
                        temp = temp / 2;
                        c[x] = c[x] * 2;
                    }
                }
            }
            #pragma acc loop vector seq gang worker independent
            for (int x = 0; x < 10 * n; ++x) {
                if (b[x] == 1) {
                    temp = a[x];
                    while (temp > 1) {
                        temp = temp / 2;
                        c[x] = c[x] * 2;
                    }
                }
                else {
                    c[x] = -1;
                }
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x) {
        if (c[x] < 0) {
            temp = a[x];
            while (temp > 1) {
                temp = temp / 2;
                c[x] = c[x] / 2;
            }
            if (c[x] != 1) {
                err++;
            }
        }
        else {
            if (c[x] != 1 << (a[x] - 1)) {
                err++;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:parallel,firstprivate,combined-constructs,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    int * a = (int *)malloc(10 * n * sizeof(int));
    int * b = (int *)malloc(10 * n * sizeof(int));
    int * c = (int *)malloc(10 * n * sizeof(int));
    int * has_visited = (int *)malloc(10 * n/10 * sizeof(int));
    int total_visited = 0;
    int * passed_a = (int *)malloc(10 * 10 * sizeof(int));
    int * passed_c = (int *)malloc(10 * 10 * sizeof(int));
    int num_in_set;
    int temp;
    int ishost = 0;
    int stored_0 = 0;

    for (int x = 0; x < 10 * n; ++x){
        a[x] = 0;
        b[x] = 0;
        c[x] = 1;
    }

    for (int x = 0; x < 10 * n; ++x){
            temp = rand() % 10;
            for (int y = 0; y < 8; ++y) {
                a[x] += 1<<y;
            }
            if (temp < 7) {
                b[x] = 1;
            }
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10*n])
    {
        #pragma acc parallel firstprivate(c)
        {
            #pragma acc loop gang independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            #pragma acc loop worker independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            #pragma acc loop vector independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }
            #pragma acc loop seq independent
            for (int x = 0; x < 10 * n; ++x) {
                c[x] = c[x] + 1;
            }

        }
        for (int x = 0; x < 10 * n; ++x) {
            if (c[x] < 5) {
                ishost = 1;
                break;
            }
        }
        if (ishost == 0) {
            for (int x = 0; x < 10 * n; ++x) {
                if (c[x] == 1) {
                    if (stored_0 == 0) {
                        stored_0 = a[x];
                    }
                    else {
                        if (stored_0 > a[x]) {
                            stored_0 = a[x];
                        }
                    }
                }
            }
            passed_a[0] = stored_0;
            passed_c[0] = 1;
            num_in_set = 1;
        }
        else {
            for (int x = 0; x < 10 * n; ++x) {
                has_visited[x] = 0;
            }
            for (int x = 0; x < 10 * n; ++x) {
                if (c[x] == 1 && b[x] == 0 && has_visited[a[x]] == 0) {
                    has_visited[a[x]] = 1;
                    passed_a[total_visited] = a[x];
                    passed_c[total_visited] = c[x];
                    total_visited++;
                }
                else if (c[x] == 2) {
                    passed_a[total_visited] = a[x];
                    passed_c[total_visited] = c[x];
                    total_visited++;
                }
            }
            num_in_set = total_visited;
        }
        for (int x = 0; x < 10 * n; ++x) {
            if (c[x] < 3 || c[x] > 16) {
                err = 1;
            }
            else if (c[x] > 4 && c[x] != 1<<((int)(log2(a[x])) + 1)) {
                err = 1;
            }
        }
        for (int x = 0; x < num_in_set; ++x) {
            for (int y = 0; y < 10; ++y) {
                if (passed_a[x] == 1<<y) {
                    break;
                }
            }
            for (int y = x + 1; y < num_in_set; ++y) {
                if (passed_a[x] == passed_a[y]) {
                    err += 1;
                    break;
                }
            }
        }
    }

    return err;
}