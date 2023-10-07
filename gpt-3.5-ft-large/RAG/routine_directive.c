void home();
int err = 0;
#pragma acc routine seq
void home() {
    #pragma acc loop
    for(int i = 0; i < 10; i++) {}
}

#pragma acc routine(home)
void nn_recurse(int * a, int n, int m);

#pragma acc routine seq
void n_recurse(int * a, int n, int m);

#pragma acc routine worker
void w_recurse(int * a, int n, int m);

#pragma acc routine vector
void v_recurse(int * a, int n, int m);

#pragma acc routine seq
void home_recurse(int * a, int n, int m);

void nn_recurse(int * a, int n, int m){
    if(m == 0){
        if(a[0] != 1){
            #pragma acc atomic update
            err += 1;
        }
    }
    else if(m % 2 == 1){
        for(int x = 0; x < n; ++x){
            #pragma acc parallel
            home_recurse(a, n, m - 1);
        }
    }
    else{
        for(int x = 0; x < n; ++x){
            #pragma acc parallel
            nn_recurse(a, n, m - 1);
        }
    }
}

#pragma acc routine seq
void n_recurse(int * a, int n, int m){
    if(m == 0){
        if(a[0] != 1){
            #pragma acc atomic update
            err += 1;
        }
    }
    else{
        for(int x = 0; x < n; ++x){
            #pragma acc parallel
            n_recurse(a, n, m - 1);
        }
    }
}

#pragma acc routine vector
void v_recurse(int * a, int n, int m){
    if(m == 0){
        if(a[0] != 1){
            #pragma acc atomic update
            err += 1;
        }
    }
    else{
        for(int x = 0; x < n; ++x){
            #pragma acc parallel
            v_recurse(a, n, m - 1);
        }
    }
}
#pragma acc routine worker
void w_recurse(int * a, int n, int m){
    if(m == 0){
        if(a[0] != 1){
            #pragma acc atomic update
            err += 1;
        }
    }
    else{
        for(int x = 0; x < n; ++x){
            #pragma acc parallel
            w_recurse(a, n, m - 1);
        }
    }
}

#pragma acc routine seq
void home_recurse(int * a, int n, int m) {
    if(m == 0){
        if(a[0] != 1){
            #pragma acc atomic update
            err += 1;
        }
    }
    else if(m % 2 == 1) {
        for(int x = 0; x < n; ++x) {
            #pragma acc parallel
            home_recurse(a, n, m - 1);
        }
    }
    else {
        for(int x = 0; x < n; ++x) {
            #pragma acc parallel
            nn_recurse(a, n, m - 1);
        }
    }
}


#pragma acc routine seq
int recurse_test(int * a, int n, int m, void (*pt2Func)(int *a, int n, int m)){
    if(m == 0){
        a[0] = 1;
        for(int x = 1; x < n; ++x){
            a[x] = a[x - 1];
        }
    }
    else{
        (*pt2Func)(a, n, m - 1);
        a[0] = a[0];
        for(int x = 1; x < n; ++x){
            a[x] = a[x - 1] + a[x];
        }
    }
    return a[n - 1];
}

int main(){
    int a[10];
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int host[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int c[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int total = 0;

    home();

    for (int x = 0; x < 10; ++x){
        total += b[x];
    }
    n_recurse(b, 10, 2);
    if (total != 57){
        err += total;
    }

    total = 0;
    for (int x = 0; x < 10; ++x){
        total += b[x];
    }
    v_recurse(b, 10, 2);
    if (total != 57){
        err += total;
    }

    total = 0;
    for (int x = 0; x < 10; ++x){
        total += b[x];
    }
    w_recurse(b, 10, 2);
    if (total != 57){
        err += total;
    }

    nn_recurse(c, 10, 9);
    total = 1;
    for (int x = 1; x < 10; ++x){
        total += c[x];
    }
    if (total != 512){
        err += 3;
    }

    recurse_test(a, 10, 10, nn_recurse);
    int passed = 1;
    int multiply = 1;
    for (int x = 0; x < 10; ++x){
        multiply *= 2;
        if (a[x] != multiply){
            passed = 0;
        }
    }

    if (passed == 0){
        err += 1;
    }

    #pragma acc parallel loop
    for (int x = 0; x < 10; ++x){
        nn_recurse(a, 10, 9);
    }
    passed = 1;
    for (int x = 0; x < 10; ++x){
        multiply = 1;
        for (int y = 0; y < x + 1; ++y){
            multiply *= 2;
        }
        for (int y = 0; y < 10 - x - 1; ++y){
            multiply *= 2;
        }
        if (a[x] != multiply){
            passed = 0;
        }
    }
    if (passed == 0){
        err += 1;
    }

    recurse_test(a, 10, 9, home_recurse);
    passed = 1;
    for (int x = 0; x < 10; ++x){
        if (a[x] != x + 1){
            passed = 0;
        }
    }
    if (passed == 0){
        err += 1;
    }