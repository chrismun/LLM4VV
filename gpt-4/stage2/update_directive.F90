#ifndef T1
!T1: update directive, V:2.7-2.3
    LOGICAL FUNCTION test1()
      USE OPENACC
      IMPLICIT NONE
      INCLUDE "acc_testsuite.Fh"

      INTEGER :: errors = 0
      INTEGER, DIMENSION(10) :: a, b
      INTEGER :: i

      ! Initialize array a on host
      DO i=1, 10
        a(i) = i
      END DO

      ! Copy array a to the device memory
      !$ACC ENTER DATA COPYIN(a)

      ! Update array b with the values of array a from the device memory
      !$ACC UPDATE SELF(b=a)

      ! Verify that the update worked
      DO i=1, 10
        IF (a(i) .NE. b(i)) THEN
          errors = errors + 1
        END IF
      END DO

      IF (errors .eq. 0) THEN
        test1 = .FALSE.
      ELSE
        test1 = .TRUE.
      END IF
    END FUNCTION test1
#endif