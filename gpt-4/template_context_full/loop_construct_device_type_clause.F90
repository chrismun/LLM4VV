#ifndef T1
!T1:loop construct device_type clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, n, sum, expected_sum
        INTEGER, DIMENSION(:), ALLOCATABLE :: a

        n = 100
        ALLOCATE (a(n))

        FORALL (i = 1:n) a(i) = i
        expected_sum = n * (n + 1) / 2

        sum = 0
        !$ACC PARALLEL NUM_GANGS(1) NUM_WORKERS(1) VECTOR_LENGTH(32) DEVICE_TYPE(GPU)
        !$ACC LOOP GANG WORKER VECTOR REDUCTION(+:sum)
        DO i = 1, n
          sum = sum + a(i)
        END DO
        !$ACC END PARALLEL

        IF (sum /= expected_sum) errors = errors + 1

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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
END PROGRAM main