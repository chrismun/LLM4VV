#ifndef T1
!T1:loop construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(100) :: a, b, c
        INTEGER :: n = 100
        REAL :: tmp
        INTEGER :: i, j, k

        DO i = 1, n
          a(i) = 0
          b(i) = i
          c(i) = i * 2
        END DO

        !$acc parallel
        !$acc loop gang
        DO k = 1, n
          !$acc loop worker private(tmp)
          DO j = 1, n
            !a single vector lane in each gang and worker assigns to tmp
            tmp = b(j) + c(j)
            !$acc loop vector
            DO i = 1, n
              !all vector lanes use the result of the above update to tmp
              a(i) = a(i) + tmp
            END DO
          END DO
        END DO
        !$acc end parallel

        DO i = 1, n
          IF (a(i) .ne. (n * (n + 1) * (2 * n + 1) / 6)) THEN
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