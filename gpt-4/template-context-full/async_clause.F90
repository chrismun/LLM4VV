#ifndef T1
    !T1:async clause,V:2.7-2.3
    LOGICAL FUNCTION test1()
      USE OPENACC
      INTEGER :: i, errors = 0
      INTEGER, DIMENSION(1000) :: A, B, C
      LOGICAL :: field

      !Initialize arrays
      DO i=1, 1000
        A(i) = i
        B(i) = i + 1
      END DO
      C = 0

      !Compute in parallel using async clause
      !$acc parallel loop async field
      DO i=1, 1000
        C(i) = A(i) + B(i)
      END DO

      errors = acc_async_test_all()
      
      IF (errors .eq. 0) THEN
        test1 = .FALSE.
      ELSE
        test1 = .TRUE.
      END IF

      CHECK_PASSED("async clause test")
    END FUNCTION test1
    #endif

    PROGRAM main
      USE OPENACC
      IMPLICIT NONE
      INTEGER :: failures = 0
      LOGICAL :: test1
      
      failures = failures + (.NOT. test1())

      IF (failures .eq. 0) THEN
        PRINT *, 'All Tests Passed'
      ELSE
        PRINT *, 'Some Tests Failed'
      END IF
    END PROGRAM main