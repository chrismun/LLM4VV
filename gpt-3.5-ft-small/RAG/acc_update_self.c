void test_acc_update_device_update_self() {
  int err = 0;
  srand(SEED);
  unsigned int * a = (unsigned int *)malloc(n * sizeof(unsigned int));
  unsigned int * b = (unsigned int *)malloc(n * sizeof(unsigned int));
  unsigned int * c = (unsigned int *)malloc(10 * n * sizeof(unsigned int));
  real_t * false_margin = (real_t *)malloc(10 * n * sizeof(real_t));

  for (unsigned int x = 0; x < n; ++x){
      a[x] = 0;
      b[x] = 1;
      for (int y = 0; y < loop_count; ++y){
          b[x] = (b[x] * 3) + 1;
      }
  }

  #pragma acc data copyin(a[0:n]) create(c[0:10 * n])
  {
    #pragma acc parallel
    {
      #pragma acc loop
      for (unsigned int x = 0; x < n; ++x){
          c[x * 10] = a[x];
          for (int y = 1; y < 10; ++y){
              c[x * 10 + y] = 0;
          }
      }
    }
  }

  for (int x = 0; x < 10; ++x){
      for (int y = 0; y < n; ++y){
          false_margin[y + x * n] = (real_t) rand() / RAND_MAX;
      }
  }

  for (int x = 0; x < 10; ++x){
      #pragma acc data copyin(b[0:n]) copyin(c[x * n: n]) copyout(a[0:n])
      {
        #pragma acc parallel
        {
          #pragma acc loop
          for (int y = 0; y < n; ++y){
              a[y] = (1 + b[y]) / 2;
              for (int z = 0; z < x; ++z){
                  a[y] = (a[y] + c[z * n + y]);
              }
          }
        }
      }
      for (int y = 0; y < n; ++y){
          a[y] = (1 + a[y] * 2) % 1024;
      }
      #pragma acc parallel
      {
        #pragma acc loop
        for (int y = 0; y < n; ++y){
            a[y] = 0;
        }
      }
      for (int y = 0; y < x + 1; ++y){
          #pragma acc data present(c[y*n:n]) copyout(a[0:n])
          {
            #pragma acc parallel
            {
              #pragma acc loop
              for (int z = 0; z < n; ++z){
                  a[z] = (a[z] + (c[y * n + z] * 3));
              }
            }
          }
          #pragma acc parallel
          {
            #pragma acc loop
            for (int z = 0; z < n; ++z){
                a[z] = (1 + a[z] * 2) % 1024;
            }
          }
          #pragma acc update self(a[0:n])
          #pragma acc parallel
          {
            #pragma acc loop
            for (int z = 0; z < n; ++z){
                a[z] = 0;
            }
          }
      }
      #pragma acc data copyin(b[0:n]) copyin(c[x * n: n]) copyout(a[0:n])
      {
        #pragma acc parallel
        {
          #pragma acc loop
          for (int y = 0; y < n; ++y){
              a[y] = (1 + b[y]) / 2;
              for (int z = 0; z < x + 1; ++z){
                  a[y] = (a[y] + c[z * n + y]);
              }
          }
        }
      }
      for (int y = 0; y < n; ++y){
          a[y] = (1 + a[y] * 2) % 1024;
      }
      for (int y = 0; y < n; ++y){
          if (fabs((real_t)a[y] - (1 + (b[y] * pow(2, x + 1)) % 1024)) > PRECISION){
              err = 1;
          }
      }
  }
  for (int x = 0; x < n; ++x){
      for (int y = 0; y < 10; ++y){
          if (fabs(false_margin[x + y * n] - c[x + y * n]) > PRECISION){
              err = 1;
          }
      }
  }

  for (int x = 0; x < 10; ++x){
      #pragma acc data copyin(b[0:n]) copyin(c[x * n: n]) copyout(a[0:n])
      {
        #pragma acc parallel
        {
          #pragma acc loop
          for (int y = 0; y < n; ++y){
              a[y] = (1 + b[y]) / 2;
              for (int z = 0; z < x; ++z){
                  a[y] = (a[y] + c[z * n + y]);
              }
          }
        }
      }
      for (int y = 0; y < n; ++y){
          a[y] = (1 + a[y] * 2) % 1024;
      }
      for (int y = 0; y < n; ++y){
          if (fabs((real_t)a[y] - (1 + (b[y] * pow(2, x)) % 1024)) > PRECISION){
              err = 1;
          }
      }
  }

  free(a);
  free(b);
  free(c);
  free(false_margin);
  if (!err) {
      printf("pass\n");
  } else {
      printf("fail\n");
  }
}

int main(){
  int failed = 0;
  failed += test_acc_update_device_update_self();
  return failed;
}