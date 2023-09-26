!T1:init directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_num = 0
        INTEGER :: device_type = acc_device_cuda      

        !$acc init if (device_num != -1 && device_type != -1)

        IF (.NOT. acc_is_initialized(device_type)) THEN
          errors = errors + 1
        END IF
          
        IF (errors .eq.0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1

        failed = .FALSE.
        failcode = 0

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF

        CALL EXIT (failcode)
      END PROGRAM main