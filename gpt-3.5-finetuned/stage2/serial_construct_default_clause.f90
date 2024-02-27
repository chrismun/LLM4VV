!T1:serial construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER, PARAMETER :: N = 1024
        REAL(8),DIMENSION(N):: a, b, c, d 
        REAL(8) :: random real
        INTEGER :: x

        SEEDDIM(1) = 1
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)
        a = 0
        d = 0

        !$ACC PARALLEL 
          !$ACC LOOP SEQ
          DO x = 1, N
            a(x) = b(x) + c(x)
          END DO 
        !$ACC END PARALLEL 

        !$ACC DATA COPY(a(1:N))
          !$ACC SERIAL LOOP DEFAULT(PRESENT)
          DO x = 1, N
            d(x) = a(x)
          END DO
        !$ACC END DATA
        DO x = 1, N
          IF (abs(d(x) - (b(x) + c(x))) .gt. epsilon) THEN
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