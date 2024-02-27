! This example tests the OpenACC loop construct vector clause.
MODULE test_module
  USE openacc
  IMPLICIT NONE
CONTAINS
  LOGICAL FUNCTION test_vector_clause()
    INTEGER, DIMENSION(1024) :: a, b, c
    INTEGER :: i, errors

    errors = 0
    ! Initialize arrays
    DO i = 1, SIZE(a)
      a(i) = i
      b(i) = SIZE(a) - i + 1
    END DO

    !$acc parallel loop vector
    DO i = 1, SIZE(a)
      c(i) = a(i) + b(i)
    END DO

    ! Check results
    DO i = 1, SIZE(a)
      IF (c(i) /= SIZE(a) + 1) THEN
        errors = errors + 1
      END IF
    END DO

    IF (errors .eq. 0) THEN
      test_vector_clause = .FALSE.
    ELSE
      test_vector_clause = .TRUE.
    END IF
  END FUNCTION test_vector_clause
END MODULE test_module

PROGRAM main
  USE test_module
  IMPLICIT NONE
  LOGICAL :: failed
  INTEGER :: failcode, testrun

  failed = .FALSE.
  failcode = 0

  DO testrun = 1, 1 ! Simplified for single test
    failed = failed .or. test_vector_clause()
  END DO
  IF (failed) THEN
    failcode = failcode + 2 ** 0
    WRITE(*,*) "Test failed."
  ELSE
    WRITE(*,*) "Test passed."
  END IF

  CALL EXIT(failcode)
END PROGRAM main