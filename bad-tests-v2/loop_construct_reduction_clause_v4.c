#ifndef T1
//T1:reduction:loopconstruct,reduction,runtime-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t b=a[0];
    real_t calc;
    int i,j;

    for (i = 0; i < 10 * n; i++)
    {
        for (j = 0; j < 10; j++){
            if (j == 0)
                a[i] = rand() / (1.0 * RAND_MAX);
            else
                a[i] += rand() / (1.0 * RAND_MAX);
        }
    }

    #pragma acc data copyin(a[0:10*n]) copy(b)
    {
        #pragma acc parallel loop reduction(max:b)
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                if (a[x * n + y] > b){
                    b = a[x * n + y];
                }
            }
        }
    }

    calc = a[0];
    for (int x = 1; x < 10 * n; ++x){
        if (calc < a[x]){
            calc = a[x];
        }
    }

    if (fabs(calc - b) > PRECISION){
        err = 1;
    }

    return err;
}
#endif

#ifndef T2
//T2:reduction:loopconstruct,reduction,runtime-data,construct-independent,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t b=1;
    real_t calc;
    int i,j;

    for (i = 0; i < 10 * n; i++)
    {
        for (j = 0; j < 10; j++){
            if (j == 0)
                a[i] = rand() / (1.0 * RAND_MAX);
            else
                a[i] += rand() / (1.0 * RAND_MAX);
        }
    }

    #pragma acc data copyin(a[0:10*n]) copy(b)
    {
        #pragma acc parallel loop reduction(min:b)
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                if (a[x * n + y] < b){
                    b = a[x * n + y];
                }
            }
        }
    }

    calc = a[0];
    for (int x = 1; x < 10 * n; ++x){
        if (calc > a[x]){
            calc = a[x];
        }
    }

    if (fabs(calc - b) > PRECISION){
        err = 1;
    }

    return err;
}
#endif

#ifndef T3
//T3:reduction:loopconstruct,reduction,runtime-data,construct-independent,V:2.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t b=0;
    real_t calc;
    int i,j;

    for (i = 0; i < 10 * n; i++)
    {
        for (j = 0; j < 10; j++){
            if (j == 0)
                a[i] = rand() / (1.0 * RAND_MAX);
            else
                a[i] += rand() / (1.0 * RAND_MAX);
        }
    }

    for (i = 0; i < 10 * n; i++)
    {
        b += a[i];
    }

    #pragma acc data copyin(a[0:10*n]) copy(b)
    {
        #pragma acc parallel loop reduction(+:b)
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                b += a[x * n + y];
            }
        }
    }

    calc = 0;
    for (int x = 0; x < 10 * n; ++x){
        calc += a[x];
    }

    if (fabs(calc - b) > PRECISION * 10 * n){
        err = 1;
    }

    return err;
}
#endif

#ifndef T4
//T4:reduction:loopconstruct,reduction,runtime-data,construct-independent,V:2.0-2.7
int test4(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t b=0;
    real_t calc;
    int i,j, exp = 5;

    for (i = 0; i < 10 * n; i++)
    {
        for (j = 0; j < 10; j++){
            if (j == 0)
                a[i] = pow(rand() / (1.0 * RAND_MAX), 10 / exp);
            else
                a[i] += pow(rand() / (1.0 * RAND_MAX), 10 / exp);
        }
    }

    for (i = 0; i < 10 * n; i++)
    {
        b += a[i];
    }
    b = pow(b, exp);

    #pragma acc data copyin(a[0:10*n]) copy(b)
    {
        #pragma acc parallel loop reduction(^:b)
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                b ^= (unsigned long long int)pow(a[x * n + y], exp);
            }
        }
    }

    calc = 0;
    for (int x = 0; x < 10 * n; ++x){
        calc += (unsigned long long int)pow(a[x], exp);
    }
    calc = pow(calc, exp);

    if (fabs(calc - b) > PRECISION * pow(10 * n, exp)){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
#pragma acc data copyin(n, failed) copyout(failed)
    {
        if (n > 0)
        {
            failed = failed + test1();
        }
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T2
    failed = 0;
#pragma acc data copyin(n, failed) copyout(failed)
    {
        failed = failed + test2();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
#pragma acc data copyin(n, failed) copyout(failed)
    {
        if (n > 0)
        {
            failed = failed + test3();
        }
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 2);
    }
#endif
#ifndef T4
    failed = 0;
#pragma acc data copyin(n, failed) copyout(failed)
    {
        failed = failed + test4();
    }

    if (failed != 0)
    {
        failcode = failcode + (1 << 3);
    }
#endif
    return failcode;
}