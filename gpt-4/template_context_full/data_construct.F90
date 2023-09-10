!acc tes suite for data construct

MODULE test_mod
  USE OPENACC
  REAL :: a(10), b(10)
END MODULE test_mod

SUBROUTINE test1()
  USE test_mod
  INTEGER :: i

  DO i = 1, 10
    a(i) = float(i)
    b(i) = 0.0
  END DO

!$acc data copyin(a) copy(b)
  DO i = 1, 10
!$acc parallel loop
    DO j = 1, 10
      b(i) = a(i)
    END DO
  END DO
!$acc end data

  IF(any(b /= a)) THEN
    PRINT *, "Test Failed"
    STOP 1
  END IF
END SUBROUTINE test1

PROGRAM main
  IMPLICIT NONE

  CALL test1()

  PRINT *,"Test passed"
END PROGRAM main