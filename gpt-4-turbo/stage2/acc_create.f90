! This code requires an OpenACC compatible compiler and the OpenACC module.
! Make sure to compile with appropriate flags, e.g., -acc for PGI compiler.
! Save this file as: acc_create_test.F90

!T1:acc create,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(100) :: testArray
        INTEGER :: i
        INTEGER :: errors = 0

        ! Initialize the array
        DO i = 1, 100
          testArray(i) = i
        END DO

        ! Using acc_create to allocate space for testArray on the device without initializing it.
        ! This is purely to test that acc_create is working as expected.
        !$acc enter data create(testArray)
        
        ! Check if testArray is present on the device using acc_is_present.
        ! If not, increment errors.
        IF (.NOT. acc_is_present(testArray, SIZEOF(testArray))) THEN
          errors = errors + 1
        END IF
        
        !$acc exit data delete(testArray)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
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
        CALL EXIT (failcode)
      END PROGRAM main