#ifndef T1
!T1:acc shutdown,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: dev_type
        INTEGER :: dev_num
        LOGICAL :: device_available

        ! Get the device type and device number
        dev_type = acc_get_device_type()
        dev_num = acc_get_device_num(dev_type)

        ! Shutdown the device
        CALL acc_shutdown(dev_type)

        ! Check if the device is still available
        device_available = acc_get_device_type() == dev_type

        ! If the device is still available, increment the error count
        IF (device_available) THEN
          errors = errors + 1
        END IF

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