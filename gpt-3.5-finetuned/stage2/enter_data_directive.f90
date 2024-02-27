!T1:enter data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER :: a(N)
        REAL(8), DIMENSION(N):: b
        REAL(8), DIMENSION(N):: c
        REAL(8):: D

        CALL RANDOM_SEED
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)

        !$acc enter data copyin(b(1:N), c(1:N)) create(a(1:N))

        !$acc data copyout(a(1:N))
          !$acc parallel
            !$acc loop
            DO I = 1,N
              a(I) = b(I) * c(I)
            END DO
        !$acc end data

        DO I = 1,N
          IF (abs(a(I) - (b(I) * c(I))) .GT. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data copyout(a(1:N)) delete(b(1:N), c(1:N))

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