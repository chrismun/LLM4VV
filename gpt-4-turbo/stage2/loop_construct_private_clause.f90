! This program tests the proper implementation of the 'private' clause in OpenACC loop constructs
PROGRAM test_private_clause
  USE openacc
  IMPLICIT NONE
  INTEGER, PARAMETER :: n = 10
  REAL, DIMENSION(n,n) :: a, b, c
  REAL :: tmp, div
  INTEGER :: i, j, k
  INTEGER :: errors

  ! Initialize arrays and div
  div = 2.0
  a = 0.0
  b = 1.0
  c = 2.0
  errors = 0

  !$acc parallel num_gangs(1) copy(a) copyin(b,c) private(tmp)
  !$acc loop gang
  DO k = 1, n
    !$acc loop worker private(tmp)
    DO j = 1, n
      tmp = b(j,k) + c(j,k)
      !$acc loop vector
      DO i = 1, n
        a(i,j,k) = a(i,j,k) + tmp / div
      ENDDO
    ENDDO
  ENDDO
  !$acc end parallel
  
  ! Verify Results - Ideally, tmp should have been private and the computation reflects that
  DO k = 1, n
    DO j = 1, n
      DO i = 1, n
        IF (ABS(a(i,j,k) - ((b(j,k) + c(j,k)) / div)) > 1.0E-6) THEN
          errors = errors + 1
        END IF
      ENDDO
    ENDDO
  ENDDO

  IF (errors == 0) THEN
    PRINT *, "Test Passed."
  ELSE
    PRINT *, "Test Failed."
  END IF
END PROGRAM test_private_clause