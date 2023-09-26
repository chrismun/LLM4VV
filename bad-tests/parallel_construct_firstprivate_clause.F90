!T1:parallel construct firstprivate clause, V:2.7-2.3
    LOGICAL FUNCTION test1()
      USE OPENACC
      IMPLICIT NONE
      INCLUDE "acc_testsuite.Fh"
      INTEGER, DIMENSION(:), ALLOCATABLE :: a, b
      INTEGER :: i, errors = 0
      
      ALLOCATE(a(1:N), b(1:N))
      
      DO i=1,N
          a(i) = i
      END DO

      b = 0  ! reset b
      
      !$ACC PARALLEL LOOP COPYIN(a) COPYOUT(b)
      DO i=1,N
          b(i) = a(i) + i
      END DO

      ! checks for incorrect results
      DO i=1,N
          IF (b(i) .NE. (2 * i)) THEN
              errors = errors + 1
          END IF
      END DO  
      
      b = 0  ! reset b
       
      !$ACC PARALLEL LOOP FIRSTPRIVATE(a) COPYOUT(b)
      DO i=1,N
          b(i) = a(i) + i
      END DO

      DO i=1,N
          IF (b(i) .NE. (2 * i)) THEN
              errors = errors + 1
          END IF
      END DO
      
      IF (errors .eq. 0) THEN
        test1 = .TRUE.
      ELSE
        test1 = .FALSE.
      END IF
    END FUNCTION test1