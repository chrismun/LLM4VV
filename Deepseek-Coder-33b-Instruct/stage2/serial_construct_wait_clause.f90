#ifndef T1
!T1:serial construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        REAL(8), DIMENSION(N) :: a, b
        REAL(8) :: sum

        ! Initialize arrays
        DO i = 1, N
          a(i) = i
          b(i) = i * 2
        END DO

        ! Compute sum on the host
        sum = 0.0
        !$acc serial
        DO i = 1, N
          sum = sum + a(i) + b(i)
        END DO
        !$acc end serial

        ! Check the result
        IF (sum .ne. N * (N + 1)) THEN
          errors = errors + 1
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