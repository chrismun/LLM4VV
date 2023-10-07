#ifndef T1
!T1:parallel construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        LOGICAL :: is_on_device
        INTEGER, DIMENSION(10) :: a
        
        ACC INITIALIZATION HERE
        ! You need to fill this part based on your system
        ! You need to initialize your device and possibly data on the device
        
        a = 0 
        !$ACC PARALLEL SELF(.TRUE.) COPYOUT(is_on_device) COPY(a)
        IF (acc_on_device(acc_device_not_host)) THEN
          is_on_device = .TRUE.
          a = 1
        ELSE
          is_on_device = .FALSE.
        END IF
        !$ACC END PARALLEL

        IF (.NOT. is_on_device .OR. ANY(a /= 1)) THEN
          errors = errors + 1
        END IF

        IF (errors == 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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
      END PROGRAM main