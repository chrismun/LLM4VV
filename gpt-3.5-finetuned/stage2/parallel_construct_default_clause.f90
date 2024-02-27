!T1:parallel construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(1:1024) :: a, b, c, d, e, f, g, h, i, j, k
        REAL(8) :: rand
        INTEGER :: x
        
        SEEDDIM(1) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)

        !$acc data copyout(a(1:n), b(1:n), c(1:n), d(1:n), e(1:n), f(1:n), g(1:n), h(1:n), i(1:n), j(1:n)) copyin(k(1:n))
          !$acc parallel default(present)
            !$acc loop
            DO x = 1, n
              a(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              b(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              c(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              d(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              e(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              f(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              g(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              h(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              i(x) = k(x) * 1
            END DO
            !$acc loop
            DO x = 1, n
              j(x) = k(x) * 1
            END DO
          !$acc end parallel
        !$acc end data
        DO x = 1, n
          IF ((abs(a(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(b(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(c(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(d(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(e(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(f(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(g(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(h(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(i(x) - (k(x) * 1)) .gt. 1.0E-8) .or. (abs(j(x) - (k(x) * 1)) .gt. 1.0E-8)) THEN
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