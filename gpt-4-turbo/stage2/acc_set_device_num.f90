!T1:acc_set_device_num,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: dev_num
        INTEGER :: selected_device_num
        INTEGER(acc_device_kind) :: dev_type

        ! Set device number and type
        dev_num = 0
        dev_type = acc_device_nvidia
        
        ! Apply acc_set_device_num
        CALL acc_set_device_num(dev_num, dev_type)

        ! Verify if the device has been set correctly
        selected_device_num = acc_get_device_num(dev_type)

        IF (selected_device_num .ne. dev_num) THEN
          errors = errors + 1
        END IF

        ! Error checking logic
        IF (errors .eq. 0) THEN
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
      END PROGRAM