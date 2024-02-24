#ifndef T1
!T1:host_data construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: a, b
        LOGICAL :: condition

        ! Initialize the condition
        condition = .FALSE.

        !$acc host_data if(condition)
        a = 1
        !$acc end host_data

        !$acc host_data if(.not. condition)
        b = 2
        !$acc end host_data

        ! Check if the values of a and b are as expected
        IF (a .ne. 1) THEN
          errors = errors + 1
        END IF
        IF (b .ne. 2) THEN
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