!T1:loop construct vector clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(N, M, P):: a, b, c
        INTEGER :: x, y, z

        SEEDDIM(1) = 1
        SEEDDIM(1) = _RAND_SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc data copyin(a(1:N, 1:M, 1:P), b(1:N, 1:M, 1:P)) copyout(c(1:N, 1:M, 1:P))
          !$acc parallel
            !$acc loop vector
            DO z = 1, P
              !$acc loop vector
              DO y = 1, M
                !$acc loop vector
                DO x = 1, N
                  c(x,y,z) = a(x,y,z) + b(x,y,z)
                END DO
              END DO
            END DO
          !$acc end parallel
        !$acc end data
        
        DO z = 1, P
          DO y = 1, M
            DO x = 1, N
              IF (abs(c(x,y,z) - (a(x,y,z) + b(x,y,z))) .gt. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO
          END DO
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