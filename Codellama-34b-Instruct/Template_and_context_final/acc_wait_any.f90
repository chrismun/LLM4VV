#ifndef T1
!T1:acc wait any,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: queue_index
        INTEGER :: wait_arg(1)
        INTEGER :: dev_num
        
        dev_num = acc_get_device_num()
        wait_arg(1) = acc_async_sync
        
        queue_index = acc_wait_any(1, wait_arg)
        
        IF (queue_index .eq. -1) THEN
          errors = errors + 1
        END IF
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif