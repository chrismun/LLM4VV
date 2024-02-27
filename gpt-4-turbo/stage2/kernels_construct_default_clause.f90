!T1:kernels construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(100) :: test_array
        INTEGER :: i
        
        ! Initialize the array
        DO i = 1, SIZE(test_array)
          test_array(i) = i
        END DO

        ! Apply the kernels construct
        !$acc kernels default(present)
        DO i = 1, SIZE(test_array)
          test_array(i) = test_array(i) * 2
        END DO
        !$acc end kernels
        
        ! Check for correctness
        DO i = 1, SIZE(test_array)
          IF (test_array(i) /= i * 2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL test1
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
      END PROGRAM