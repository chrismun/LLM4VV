#ifndef T1
//T1:loop,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    int i, j;
    char * a = (char *)malloc(100 * n * sizeof(char));
    char * b = (char *)malloc(n * sizeof(char));
    srand(1);
    for (i = 0; i < 100; ++i){
        for (j = 0; j < n; ++j){
            a[i * n + j] = (char) rand();
        }
    }
    for (j = 0; j < n; ++j){
        b[j] = rand() % 127;
    }
    #pragma acc data copyin(a[0:100*n]) copy(b[0:n])
    {
      #pragma acc cache(a[0:100*n])
      #pragma acc parallel present(a[0:100*n])
      {
          #pragma acc loop
          for (i = 0; i < 100; ++i){
              char rolling = (char)1;
              #pragma acc loop seq
              for (j = 0; j < n; ++j){
                  char temp;
                  temp = a[i * n + j];
                  a[i * n + j] = rolling * b[j];
                  rolling = temp;
              }
          }
      }
    }
    for (i = 0; i < 100; ++i){
        for (j = 0; j < n; ++j){
            if (a[i * n + j] != (((i / 20 + 1) * (i / 20 - 2) / 2) % 2) * b[j]){
                err += 1;
                break;
            }
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:loop,construct-independent,V:2.5-2.7
int test2(){
    int err = 0;
    int i, j;
    char * a = (char *)malloc(100 * n * sizeof(char));
    char * b = (char *)malloc(n * sizeof(char));
    srand(1);
    for (i = 0; i < 100; ++i){
        for (j = 0; j < n; ++j){
            a[i * n + j] = (char) rand();
        }
    }
    for (j = 0; j < n; ++j){
        b[j] = rand() % 127;
    }
    #pragma acc data copyin(a[0:100*n]) copy(b[0:n])
    {
      #pragma acc cache(a[0:100*n, 10:62])
      #pragma acc parallel present(a[0:100*n])
      {
          #pragma acc loop
          for (i = 0; i < 100; ++i){
              char rolling = (char)1;
              #pragma acc loop seq
              for (j = 10; j < 63; ++j){
                  char temp;
                  temp = a[i * n + j];
                  a[i * n + j] = rolling * b[j - 10];
                  rolling = temp;
              }
          }
      }
    }
    for (i = 0; i < 100; ++i){
        for (j = 0; j < 63; ++j){
            if (a[i * n + j] != (((i / 20 + 1) * (i / 20 - 2) / 2) % 2) * b[j - 10]){
                err += 1;
                break;
            }
        }
        for (j = 63; j < n; ++j){
            if (a[i * n + j] != (i % 8) * b[j - 53]){
                err += 1;
                break;
            }
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:loop,construct-independent,V:2.5-2.7
int test3(){
    int err = 0;
    int i, j;
    char * a = (char *)malloc(100 * n * sizeof(char));
    char * b = (char *)malloc(100 * sizeof(char));
    char * c = (char *)malloc(n * sizeof(char));
    srand(1);
    for (i = 0; i < 100; ++i){
        for (j = 0; j < n; ++j){
            a[i * n + j] = (char) rand();
        }
    }
    for (j = 0; j < n; ++j){
        c[j] = rand() % 127;
    }
    for (i = 0; i < 100; ++i){
        b[i] = rand() % 127;
    }
    #pragma acc data copyin(a[0:100*n]) copy(b[0:100], c[0:n])
    {
      #pragma acc cache(a[0:100*n, 0:n], b[0:100])
      #pragma acc parallel present(a[0:100*n])
      {
          #pragma acc loop
          for (i = 0; i < 100; ++i){
              char res = b[i];
              #pragma acc loop seq
              for (j = 0; j < n; ++j){
                  res += a[i * n + j] * c[j];
                  a[i * n + j] = res;
              }
          }
      }
    }
    for (i = 0; i < 100; ++i){
        char res = b[i];
        for (j = 0; j < n; ++j){
            res += a[i * n + j] * c[j];
            a[i * n + j] = res;
        }
        for (j = 0; j < n; ++j){
            if (a[i * n + j] != res){
                err += 1;
                break;
            }
        }
    }

    return err;
}
#endif

#ifndef T4
//T4:loop,construct-independent,V:2.5-2.7
int test4(){
    int err = 0;
    int i, j;
    char * a = (char *)malloc(100 * n * sizeof(char));
    char * b = (char *)malloc(100 * sizeof(char));
    char * c = (char *)malloc(n * sizeof(char));
    srand(1);
    for (i = 0; i < 100; ++i){
        for (j = 0; j < n; ++j){
            a[i * n + j] = (char) rand();
        }
    }
    for (j = 0; j < n; ++j){
        c[j] = rand() % 127;
    }
    for (i = 0; i < 100; ++i){
        b[i] = rand() % 127;
    }
    #pragma acc data copyin(a[0:100*n]) copy(b[0:100], c[0:n])
    {
      #pragma acc cache(a[0:100*n, 0:n], b[0:100])
      #pragma acc parallel present(a[0:100*n])
      {
          #pragma acc loop
          for (i = 0; i < 100; ++i){
              char x = b[i];
              #pragma acc loop seq
              for (j = 0; j < n; ++j){
                  a[i * n + j] = x * a[i * n + j] * c[j];
              }
          }
      }
    }
    for (i = 0; i < 100; ++i){
        char x = b[i];
        for (j = 0; j < n; ++j){
            if (a[i * n + j] != x * x * c[j]){
                err += 1;
                break;
            }
        }
    }

    return err;
}
#endif

#ifndef T5
//T5:loop,construct-independent,V:2.5-2.7
int test5(){
    int err = 0;
    int i, j;
    char * a = (char *)malloc(100 * n * sizeof(char));
    char * b = (char *)malloc(100 * sizeof(char));
    char * c = (char *)malloc(n * sizeof(char));
    for (i = 0; i < 100; ++i){
        for (j = 0; j < n; ++j){
            a[i * n + j] = (char) 1;
        }
    }
    for (j = 0; j < n; ++j){
        c[j] = 2;
    }
    for (i = 0; i < 100; ++i){
        b[i] = 3;
    }
    #pragma acc data copyin(a[0:100*n]) copy(b[0:100], c[0:n])
    {
      #pragma acc cache(a[0:100*n, 0:n], b[0:100])
      #pragma acc parallel present(a[0:100*n])
      {
          #pragma acc loop
          for (i = 0; i < 100; ++i){
              char res = b[i];
              #pragma acc loop seq
              for (j = 0; j < n; ++j){
                  res += a[i * n + j] * c[j];
                  a[i * n + j] = res;
              }
          }
      }
    }
    for (i = 0; i < 100; ++i){
        char res = b[i];
        for (j = 0; j < n; ++j){
            res += a[i * n + j] * c[j];
            a[i * n + j] = res;
        }
        for (j = 0; j < n; ++j){
            if (a[i * n + j] != res){
                err += 1;
                break;
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