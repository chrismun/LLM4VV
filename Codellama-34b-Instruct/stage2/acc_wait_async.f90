#include <openacc.h>

#ifndef T1
!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async_arg = 1
        INTEGER :: wait_arg = 2
        INTEGER :: dev_num = 3
        
        CALL acc_wait_async(wait_arg, async_arg)
        CALL acc_wait_device_async(wait_arg, async_arg, dev_num)
        CALL acc_wait_all_async(async_arg)
        CALL acc_wait_all_device_async(async_arg, dev_num)
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM