! Test for OpenACC kernels construct vector_length clause.
!T1:kernels construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: N = 1024
        REAL, DIMENSION(N) :: A, B, C
        INTEGER :: i, errors
        REAL, DIMENSION(N) :: expected_C
        errors = 0

        ! Initialize arrays
        DO i = 1, N
          A(i) = REAL(i)
          B(i) = REAL(N - i + 1)
          expected_C(i) = A(i) + B(i)
        END DO

        ! Apply kernels construct with vector_length clause
        !$acc kernels vector_length(128)
        DO i = 1, N
          C(i) = A(i) + B(i)
        END DO
        !$acc end kernels

        ! Verify results
        DO i = 1, N
          IF (C(i) /= expected_C(i)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors == 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        
        EXTERNAL :: test1
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