#ifndef T1
!T1:variable predetermined data attributes,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, j
        REAL(8), DIMENSION(LOOPCOUNT) :: a, b, c

        DO i = 1, LOOPCOUNT
          a(i) = 1.0
          b(i) = 2.0
        END DO

!$acc parallel loop private(i)
        DO i = 1, LOOPCOUNT
          c(i) = a(i) + b(i)
        END DO
!$acc end parallel loop

        DO i = 1, LOOPCOUNT
          IF (c(i) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

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