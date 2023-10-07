int test_firstprivate()
{
  int err = 0;
  int i, j, dev = 0;
  int *a;

  for (j = 0; j < 1000; ++j){
    #pragma acc compute device(dev) program seq
    {
      int x  = -1;
      x += 1;
      dev = x;
      
      a = (int *)malloc(1000 * sizeof(int));
     
      for (i = 0; i < 1000; ++i){
        a[i] = 1;
      }
      #pragma acc compute firstprivate(a)
      {
          for (i = 0; i < 1000; ++i){
          }
      }
      
      for (i = 0; i < 1000; ++i){
        if (a[i] != 1){
          err += 1;
        }
      }
    }
  }

  return err;
}

int main()
{
    int failed = 0;
    
    failed += test_firstprivate();
    
    return failed;
}