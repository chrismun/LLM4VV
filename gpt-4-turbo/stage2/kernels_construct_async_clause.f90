! Make sure OpenACC is supported and available
!T1:kernels construct async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, DIMENSION(100) :: a
        INTEGER :: i
        INTEGER :: errors = 0

        ! Initialize the array a
        DO i=1, 100
          a(i) = i
        END DO

        ! Use kernels construct with async clause for a computation
        !$acc kernels async(1)
        DO i=1, 100
          a(i) = a(i) + 1
        END DO
        !$acc end kernels

        !$acc wait(1)

        ! Check the results
        DO i=1, 100
          IF (a(i) /= i+1) THEN
            errors = errors + 1
          END IF
        END DO

        ! Determine if test passed or failed
        IF (errors .eq. 0) THEN
          test1 = .FALSE.   ! Test passed
        ELSE
          test1 = .TRUE.    ! Test failed
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
        CALL EXIT(failcode)
      END PROGRAM main