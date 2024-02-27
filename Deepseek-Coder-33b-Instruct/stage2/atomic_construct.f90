!T1:atomic construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: i, v
        INTEGER, DIMENSION(:), ALLOCATABLE :: a

        ALLOCATE(a(N))

        !$acc data copy(a)
        !$acc parallel loop
        DO i = 1, N
          a(i) = i
        END DO
        !$acc end parallel loop
        !$acc end data

        v = 0
        !$acc atomic update
        v = v + 1
        !$acc end atomic

        !$acc parallel loop
        DO i = 1, N
          !$acc atomic update
          a(i) = a(i) + v
          !$acc end atomic
        END DO
        !$acc end parallel loop

        !$acc parallel loop
        DO i = 1, N
          IF (a(i) .NE. i + v) THEN
            errors = errors + 1
          END IF
        END DO
        !$acc end parallel loop

        DEALLOCATE(a)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
