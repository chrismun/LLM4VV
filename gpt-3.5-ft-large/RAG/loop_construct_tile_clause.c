#ifndef T1
//T1:loop,tile,construct-independent,V:2.6-2.7
int test1(){
  int err = 0;
  srand(SEED);
  real_t * a = (real_t *)malloc(n * sizeof(real_t));
  real_t * a_copy = (real_t *)malloc(n * sizeof(real_t));
  real_t * b = (real_t *)malloc(n * sizeof(real_t));
  real_t * b_copy = (real_t *)malloc(n * sizeof(real_t)));

  for (int x = 0; x < n; ++x){
      a[x] = rand() / (real_t)(RAND_MAX / 10);
      a_copy[x] = a[x];
      b[x] = rand() / (real_t)(RAND_MAX / 10);
      b_copy[x] = b[x];
  }

  #pragma acc data copy(a[0:n], b[0:n])
  {
      #pragma acc loop tile(2, 2) independent
      for (int x = 0; x < n; ++x){
          a[x] = a[x] + b[x];
      }
  }

  for (int x = 0; x < n; ++x){
      if (fabs(a[x] - (a_copy[x] + b_copy[x])) > PRECISION) {
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
    return failcode;
}