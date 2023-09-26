#ifndef T1
!T1:loop construct collapse clause,V:2.7-2.3
      LOGICAL FUNCTION test_collapse_clauses()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10,10) :: a, b
        INTEGER :: i, j

        a = 0
        b = 0

        !$acc parallel loop collapse(2)
        DO i = 1, 10
           DO j = 1, 10
              a(i,j) = i + j
           END DO
        END DO

        DO i = 1, 10
           DO j = 1, 10
              b(i,j) = i + j
              IF (b(i,j) .NE. a(i,j)) THEN
                 errors = errors + 1
              END IF
           END DO
        END DO

        IF (errors .eq. 0) THEN
          test_collapse_clauses = .FALSE.
        ELSE
          test_collapse_clauses = .TRUE.
        END IF
      END FUNCTION test_collapse_clauses
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test_collapse_clauses
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test_collapse_clauses()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main