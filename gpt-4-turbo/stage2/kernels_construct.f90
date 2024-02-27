! This is a dummy acc_testsuite.Fh content for demonstration purposes.
! It can be expanded according to actual test suite needs.
MODULE acc_testsuite
  IMPLICIT NONE
  INTEGER, PARAMETER :: NUM_TEST_CALLS = 10
END MODULE acc_testsuite

!T1:kernels construct,V:2.7-2.3
MODULE test_module
  USE openacc
  USE acc_testsuite
  IMPLICIT NONE

CONTAINS

  LOGICAL FUNCTION test1()
    ! Using OpenACC
    INTEGER, DIMENSION(1024) :: A
    INTEGER :: i, errors

    errors = 0

    !$acc kernels
    DO i = 1, SIZE(A)
      A(i) = i
    END DO
    !$acc end kernels

    DO i = 1, SIZE(A)
      IF (A(i) /= i) THEN
        errors = errors + 1
      END IF
    END DO

    IF (errors == 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
  END FUNCTION test1

END MODULE test_module

PROGRAM main
  USE acc_testsuite
  USE test_module
  IMPLICIT NONE
  INTEGER :: failcode, testrun
  LOGICAL :: failed, test1_result

  failed = .FALSE.
  failcode = 0

  DO testrun = 1, NUM_TEST_CALLS
    test1_result = test1()
    failed = failed .OR. test1_result
  END DO

  IF (failed) THEN
    failcode = failcode + 2 ** 0
  END IF

  PRINT *, "Failure Code:", failcode
  STOP failcode
END PROGRAM main