!T1:reference counters,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N = 1024
        REAL(8), DIMENSION(N,N) :: a, b, c
        INTEGER :: i, j
        REAL(8) :: drand
        INTEGER :: errors = 0

        SEEDDIM(1) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc enter data create(c(:,1:N))
        !$acc enter data create(c(1:N,:))
        !$acc data copyin(a(1:N,:)) copyin(b(:,1:N))
          !$acc parallel
            !$acc loop
            DO i = 1, N
              !$acc enter data copyin(c(:,i))
              !$acc loop
              DO j = 1, N
                c(j,i) = c(j,i) + a(i,j) + b(j,i)
              END DO
              !$acc exit data copyout(c(:,i))
            END DO
          !$acc end parallel
        !$acc end data
        !$acc exit data delete(c(1:N,:))
        !$acc exit data delete(c(:,1:N))

        DO i = 1, N
          DO j = 1, N
            IF (abs(c(i,j) - (a(i,j) + b(j,i))) .gt. 2 * PRECISION) THEN
              errors = errors + 1
            END IF
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