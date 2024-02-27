!T1:parallel construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(10) :: testArray
        INTEGER :: i, errors
        errors = 0

        ! Initialize array
        DO i = 1, 10
          testArray(i) = i
        END DO

        ! Parallel region with default present
        !$acc parallel loop default(present)
        DO i = 1, 10
          ! Double each element. This operation requires the compiler to correctly handle the default clause
          testArray(i) = testArray(i) * 2
        END DO
        !$acc end parallel loop

        ! Check if the array has been correctly modified
        DO i = 1, 10
          IF (testArray(i) /= i * 2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL :: test1
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT(failcode)
      END PROGRAM main