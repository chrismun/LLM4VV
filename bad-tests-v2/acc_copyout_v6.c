python
import subprocess
import random
import numpy as np

def check_open_acc_copyout(n=10):
    A = list(np.random.uniform(0,10,n))
    B = [0]*n

    open_acc_code = f'''
    #include <stdio.h>

    int main() {{
        float A[10] = {str(A).replace('[', '{').replace(']', '}').replace(' ', '')};
        float B[10];

        #pragma acc data copyin(A)
        {{
            #pragma acc kernels copyout(B)
            {{
                #pragma acc loop
                for (int i=0; i<10; i++) {{
                    B[i] = A[i];
                }}
            }}
        }}

        for(int i=0; i<10; i++) {{
            printf("%.2f\\n", B[i]);
        }}

        return 0;
    }}
    '''

    with open("copyout_test.c", "w") as file:
        file.write(open_acc_code)

    compile_cmd = "pgcc -acc -ta=nvidia -Minfo=accel copyout_test.c -o copyout_test"
    run_cmd = "./copyout_test"

    subprocess.call(compile_cmd, shell=True)
    result = subprocess.check_output(run_cmd, shell=True).decode('utf-8').split('\n')[:-1]
    
    B_result = [float(x) for x in result]
    
    assert np.isclose(np.array(A), np.array(B_result), atol=0.01).all(), "Copyout didn't work as expected"
    
    print('OpenACC copyout functionality is working correctly.')

check_open_acc_copyout()