!T1:parallel construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(9999):: a, b, c
        INTEGER :: n = 9999
        INTEGER :: x

        a = 0
        b = 0
        c = 0

        a(7) = 13
        !$acc enter data copyin(a(1:n))
        !$acc update self(a(1:n))
        !$acc parallel present(a(1:n), b(1:n), c(1:n)) wait(a, c)
          !$acc loop
          DO x = 1,n
            b(x) = a(x)
          END DO
          !$acc loop
          DO x = 1,n
            c(x) = b(x)
          END DO
        !$acc end parallel
        !$acc exit data delete(a(1:n))

        DO x = 1, n
          IF (abs(a(x) - b(x)).GT.(2*n)) THEN
            errors = errors + 1
          ELSE IF (abs(c(x) - b(x)).GT.(2*n)) THEN
            errors = errors + 1
          END IF
        END DO


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