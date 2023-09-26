!T1:acc shutdown,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(acc_device_kind) :: dev_type = acc_device_nvidia // replace with your device type
        INTEGER :: dev_num

        dev_num = acc_get_num_devices(dev_type)
        IF (dev_num > 0) THEN
          CALL acc_set_device_type(dev_type)
          CALL acc_set_device_num(1, dev_type)
          CALL acc_init(dev_type)
          CALL acc_shutdown_device(1, dev_type)
          IF (.NOT. acc_is_present(A, SIZE(A))) THEN
            errors = errors + 1
          END IF
          CALL acc_shutdown(dev_type)
          IF (acc_get_num_devices(dev_type) > 0) THEN
            errors = errors + 1
          END IF
        END IF

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1

! Main program
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
      END PROGRAM main