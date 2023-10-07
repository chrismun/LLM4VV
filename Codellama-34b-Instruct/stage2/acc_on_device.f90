#include <openacc.h>

#ifndef T1
!T1:acc on device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! Check if the code is running on the host
        IF (acc_on_device(acc_device_host) .EQV. .TRUE.) THEN
          errors = errors + 1
        END IF

        ! Check if the code is running on a device that is not the host
        IF (acc_on_device(acc_device_not_host) .EQV. .FALSE.) THEN
          errors = errors + 1
        END IF

        ! Check if the code is running on a specific device
        IF (acc_on_device(acc_device_type_nvidia) .EQV. .TRUE.) THEN
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