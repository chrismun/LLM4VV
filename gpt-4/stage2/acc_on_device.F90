!T1:acc on device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(ACC_DEVICE_KIND), PARAMETER :: DEVICE = ACC_DEVICE_TYPE_host
        
        ! Test if code is running on host device
        IF (.NOT. ACC_ON_DEVICE(DEVICE)) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OPENACC
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