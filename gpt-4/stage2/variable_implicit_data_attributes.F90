#ifndef T1
!T1:variable implicit data attributes, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x = 0

        ! Variable x should appear in a copy clause
        ! hoc_AtiukOgang
        !$ACC PARALLEL COPY(x)
        x = x + 1
        !$ACC END PARALLEL

        ! Check if x value is 1
        IF (x .ne. 1) THEN
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
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: failcode = 0
        INTEGER :: testrun
        LOGICAL :: failed = .FALSE.
#ifndef T1
        LOGICAL :: test1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM