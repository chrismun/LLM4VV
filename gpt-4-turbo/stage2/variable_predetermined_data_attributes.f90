! Example header file content for "acc_testsuite.Fh" (for simulation)
MODULE acc_testsuite
    INTEGER :: NUM_TEST_CALLS = 1
END MODULE acc_testsuite

! Main Fortran program with test1 function designed to check OpenACC implementation of 
! variable predetermined data attributes.
      MODULE mod_test1
        USE OPENACC
        IMPLICIT NONE
      CONTAINS
        LOGICAL FUNCTION test1()
          IMPLICIT NONE
          INTEGER :: i, sum, expectedSum
          INTEGER :: errors = 0
          INTEGER, DIMENSION(10) :: a
          
          sum = 0
          expectedSum = 0
          ! Use OpenACC data construct to allocate array 'a' on the device and initialize it.
          !$acc data copy(a)
          a = 0
          ! Parallel loop with each iteration of 'i' predetermined as private
          !$acc parallel loop copy(sum)
          DO i=1,10
             a(i) = i
             sum = sum + i
          END DO
          !$acc end data
          
          ! Calculate expected sum to verify correctness
          DO i=1,10
             expectedSum = expectedSum + i
          END DO
          
          ! If the actual sum differs, increment errors
          IF (sum .ne. expectedSum) THEN
             errors = errors + 1
          END IF
          
          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .TRUE.
          END IF
        END FUNCTION test1
      END MODULE mod_test1

      PROGRAM main
        USE acc_testsuite
        USE mod_test1
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        PRINT *, "Failcode:", failcode
        STOP
      END PROGRAM