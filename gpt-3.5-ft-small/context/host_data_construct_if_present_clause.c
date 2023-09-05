#include "omp_testsuite.h"
int passed;
double sprod[6], sprod_true = 1.0;
#define EPSILON 0.1E-5

int test_present (){}

int main () {  
  int _ret_val_0;
  /* int failed_old, failed_new; #<{(| Used for counting errors.  */
  /*    'failed_newbecause the fail count was zero while failing.  */
  unsigned int* status = tGet_status ();
  /* failed_old= *status; */
  single_test_start ();
  /* failed_new= *status; */
  

  test_present ();

  passed = 1;
  /*     *status = failed_old + !passed + !failed_new; */
  if (0 == passed)
    {
      _ret_val_0 = 1;
      return _ret_val_0;
    }
  return _ret_val_0;
}

int test_present() {
  int _ret_val_0;
  int i;
  double x[6], y[6];
  for (i = 0; i <= 5; i += 1) {
    /* sprod[i] = -900.0; */
    x[i] = 3.1415 * i;
    y[i] = 1.742 * i;
  }
/* I guess the default openacc host_data behavior is undefined in this */
/* case.  The initial values for sprod cannot be expected to be visible */
/* to the host.  Which is interesting behavior.  */
/* In fact, in the section that discusses the host_data behavior, it */
/* states that the default behavior when a constructor is not used */
/* is not defined.
 */
/* register present clause.  */
  for (i = 0; i <= 5; i += 1) {
    sprod[0] += x[i] * y[i];
  }
  #pragma acc data copyin(x[0:6], y[0:6]) copy(sprod[0:6])
  {
    #pragma acc parallel
    {
      #pragma acc loop
      for (i = 0; i <= 5; i += 1) {
        /* sprod[i] = 1.0;         */
        #pragma acc loop
        for (i = 0; i <= 5; i += 1) {
          sprod[1] += x[i] * y[i];
        }
        /* sprod[i] = 2.0;         */
        
        #pragma acc loop
        for (i = 0; i <= 5; i += 1) {
          sprod[2] += x[i] * y[i];
        }
        
        #pragma acc loop
        for (i = 0; i <= 5; i += 1) {
          sprod[3] += x[i] * y[i];
        }
        
        #pragma acc loop
        for (i = 0; i <= 5; i += 1) {
          sprod[4] += x[i] * y[i];
        }
        
        #pragma acc loop
        for (i = 0; i <= 5; i += 1) {
          sprod[5] += x[i] * y[i];
        }
      }
    }
  }
  /* check if everything set up correctly.  */
  for (i = 0; i <= 5; i += 1) {
    if (fabs (sprod[i] - sprod_true) >= EPSILON * sprod_true) {
      passed = 0;
      #pragma omp critical
      {
        fail_code ();
      }
    }
  }
  /* restore sprod values to '1'.  */
  for (i = 0; i <= 5; i += 1) {
    sprod[i] = sprod_true;
  }
  
  for (i = 0; i <= 5; i += 1) {
    if (sprod[i] != sprod_true) {
      passed = 0;
    }
  }
  #pragma acc data copyin(x[0:6], y[0:6]) copy(sprod[0:6])
  {
    #pragma acc host_data use_device(sprod)
    {
      #pragma acc update self(sprod[0:6])
      {
        #pragma acc parallel
        {
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            if (fabs (sprod[i]) >= EPSILON * sprod_true) {
              passed = 0;
              #pragma omp critical
              {
                fail_code ();
              }
            }
          }
        }
      }
    }
  }
  /* restore sprod values to '1'.  */
  for (i = 0; i <= 5; i += 1) {
    sprod[i] = sprod_true;
  }
  #pragma acc data copyin(x[0:6], y[0:6]) copy(sprod[0:6])
  {
    #pragma acc parallel
    {
      #pragma acc loop independent
      for (i = 0; i <= 5; i += 1) {
        {
          #pragma acc loop seq
          for (i = 0; i <= 5; i += 1) {
            sprod[1] += x[i] * y[i];
          }
          /* sprod[i] = 2.0;         */
          
          #pragma acc loop seq
          for (i = 0; i <= 5; i += 1) {
            sprod[2] += x[i] * y[i];
          }
          
          #pragma acc loop seq
          for (i = 0; i <= 5; i += 1) {
            sprod[3] += x[i] * y[i];
          }
          
          #pragma acc loop seq
          for (i = 0; i <= 5; i += 1) {
            sprod[4] += x[i] * y[i];
          }
          
          #pragma acc loop seq
          for (i = 0; i <= 5; i += 1) {
            sprod[5] += x[i] * y[i];
          }
        }
      }
    }
  }
  /* check if everything is correct after loopings.  */
  for (i = 0; i <= 5; i += 1) {
    if (fabs (sprod[i] - (6.0 * sprod_true)) >= EPSILON * sprod_true) {
      passed = 0;
      #pragma omp critical
      {
        fail_code ();
      }
    }
  }
  #pragma acc data copyin(x[0:6], y[0:6]) copy(sprod[0:6])
  {
    #pragma acc host_data use_device(sprod)
    {
      #pragma acc update self(sprod[0:6])
      {
        #pragma acc parallel
        {
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            if (fabs (sprod[i] - (3.0 * sprod_true)) >= EPSILON * sprod_true) {
              passed = 0;
              #pragma omp critical
              {
                fail_code ();
              }
            }
          }
        }
      }
    }
  }
  #pragma acc data copyin(x[0:6], y[0:6]) copy(sprod[0:6])
  {
    #pragma acc parallel
    {
      #pragma acc loop independent
      for (i = 0; i <= 5; i += 1) {
        sprod[0] += x[i] * y[i];
      }
    }
  }
  #pragma acc data copyin(x[0:6], y[0:6])
  {
    #pragma acc parallel
    {
      #pragma acc loop independent
      for (i = 0; i <= 5; i += 1) {
        sprod[0] += x[i] * y[i];
      }
    }
  }
  /* check if everything is correct after loopings.  */
  for (i = 0; i <= 5; i += 1) {
    if (fabs (sprod[i] - (6.0 * sprod_true)) >= EPSILON * sprod_true) {
      passed = 0;
      #pragma omp critical
      {
        fail_code ();
      }
    }
  }
  #pragma acc data copyin(x[0:6], y[0:6]) copy(sprod[0:6])
  {
    #pragma acc parallel
    {
      #pragma acc loop independent
      for (i = 0; i <= 5; i += 1) {
        {
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[1] += x[i] * y[i];
          }
          /* sprod[i] = 2.0;         */
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[2] += x[i] * y[i];
          }
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[3] += x[i] * y[i];
          }
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[4] += x[i] * y[i];
          }
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[5] += x[i] * y[i];
          }
        }
      }
    }
  }
  /* check if everything is correct after loopings.  */
  for (i = 0; i <= 5; i += 1) {
    if (fabs (sprod[i] - (12.0 * sprod_true)) >= EPSILON * sprod_true) {
      passed = 0;
      #pragma omp critical
      {
        fail_code ();
      }
    }
  }
  /* fail if the passed control of parallel is greater or less than 2 each.  */
  #pragma acc data copyin(x[0:6], y[0:6])
  {
    {
      #pragma acc loop independent
      for (i = 0; i <= 5; i += 1) {
        {
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[1] += x[i] * y[i];
          }
          /* sprod[i] = 2.0;         */
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[2] += x[i] * y[i];
          }
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[3] += x[i] * y[i];
          }
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[4] += x[i] * y[i];
          }
          
          #pragma acc loop independent
          for (i = 0; i <= 5; i += 1) {
            sprod[5] += x[i] * y[i];
          }
        }
      }
    }
  }
  /* check if everything is correct after loopings.  */
  for (i = 0; i <= 5; i += 1) {
    if (fabs (sprod[i] - (18.0 * sprod_true)) >= EPSILON * sprod_true) {
      passed = 0;
      #pragma omp critical
      {
        fail_code ();
      }
    }
  }
  _ret_val_0 = 0;
  return _ret_val_0;
}
#else

int main () {return 0;