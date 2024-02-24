#ifndef T1
!T1:kernels construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: i, num_gangs
        INTEGER, DIMENSION (N) :: a, b, c

        ! Initialize arrays
        DO i = 1, N
          a(i) = i
          b(i) = N - i + 1
        END DO

        !$acc kernels num_gangs(10)
        !$acc loop gang vector
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end kernels

        ! Verify results
        num_gangs = 0
        !$acc kernels num_gangs(10)
        !$acc loop gang vector reduction(+:num_gangs)
        DO i = 1, N
          IF (c(i) /= a(i) + b(i)) num_gangs = num_gangs + 1
        END DO
        !$acc end kernels

        IF (num_gangs /= 0) THEN
          errors = errors + 1
          PRINT *, "Error: num_gangs is not as expected"
        END IF

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