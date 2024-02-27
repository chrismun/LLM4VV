!T1:serial construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        REAL(KIND=4), DIMENSION(N) :: a, b, c
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, N
          a(i) = 1.0 * i
          b(i) = 2.0 * i
        END DO

        !$acc serial num_workers(1) copy(a, b, c)
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end serial

        ! Verify results
        DO i = 1, N
          IF (c(i) .ne. 3.0 * i) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
