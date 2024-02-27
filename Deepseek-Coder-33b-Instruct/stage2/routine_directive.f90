!T1:routine directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        REAL, DIMENSION(N) :: a, b, c
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, N
          a(i) = i * 1.0
          b(i) = i * 2.0
        END DO

        !$acc data copyin(a, b) copyout(c)
        !$acc parallel loop
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end data

        ! Check the results
        DO i = 1, N
          IF (c(i) .ne. a(i) + b(i)) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
