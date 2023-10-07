#ifndef T1
!T1:acc wait any,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async1, async2, async3
        INTEGER :: wait_arg(3)
        INTEGER :: index

        ! Initialize async handles
        async1 = acc_async_sync
        async2 = acc_async_sync
        async3 = acc_async_sync

        ! Launch some async operations
        ! ...

        ! Wait for any of the operations to complete
        wait_arg(1) = async1
        wait_arg(2) = async2
        wait_arg(3) = async3
        index = acc_wait_any(3, wait_arg)

        ! Check if the index is within the expected range
        IF (index .LT. 1 .OR. index .GT. 3) THEN
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