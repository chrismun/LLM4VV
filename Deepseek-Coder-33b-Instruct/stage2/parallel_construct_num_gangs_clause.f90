!T1:parallel construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: i, num_gangs
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, b

        ! Allocate memory for arrays
        ALLOCATE(a(N), b(N))

        ! Initialize arrays
        DO i = 1, N
          a(i) = i
          b(i) = 0
        END DO

        !$ACC PARALLEL NUM_GANGS(10) COPY(a, b)
        !$ACC LOOP GANG
        DO i = 1, N
          b(i) = a(i)
        END DO
        !$ACC END PARALLEL

        ! Check the results
        num_gangs = 0
        DO i = 1, N
          IF (b(i) /= a(i)) THEN
            errors = errors + 1
          END IF
          IF (MOD(i, N / 10) == 0) THEN
            num_gangs = num_gangs + 1
          END IF
        END DO

        IF (num_gangs /= 10) THEN
          errors = errors + 1
        END IF

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