int test_data();
}

int main(){
  int err = 0;
  int failcode = 0;
  int l_errors = 0;

  l_errors = 0;
  for (int x = 0; x < 10; ++x){
      if (x < 3){
          l_errors += test_data();
      }
  }
  failcode = failcode || (l_errors != 0);

  return failcode;
}