!T1:acc on device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        
        INTEGER :: errors = 0

        ! Test if running on host returns true when it should
        IF (.NOT. acc_on_device(acc_device_host)) THEN
            errors = errors + 1
        END IF
        
        ! Ensure running on any device (not host) returns false since we are not in a device region
        IF (acc_on_device(acc_device_not_host)) THEN
            errors = errors + 1
        END IF

        IF (errors == 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        
        DO testrun = 1, 1 ! As it's a simple test, one run should suffice
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT(failcode)
      END PROGRAM