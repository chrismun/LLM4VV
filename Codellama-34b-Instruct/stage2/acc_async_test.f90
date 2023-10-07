#ifndef T1
!T1:acc async test,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: wait_arg
        INTEGER :: dev_num
        
        wait_arg = 1
        dev_num = 1
        
        CALL acc_async_test(wait_arg, dev_num)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif