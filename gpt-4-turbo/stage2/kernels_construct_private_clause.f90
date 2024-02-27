!T1:kernels construct private clause,V:2.7-2.3
      MODULE testmodule
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
      CONTAINS
        LOGICAL FUNCTION test1()
          INTEGER :: errors = 0
          INTEGER :: i, privateVar
          INTEGER, DIMENSION(10) :: a

          !Initialise array with zeros
          a = 0

          !$acc kernels private(privateVar)
          DO i = 1, 10
              privateVar = i
              a(i) = privateVar
          END DO
          !$acc end kernels

          !Verify that each element of 'a' matches its expected value
          DO i = 1, 10
            IF (a(i) /= i) THEN
              errors = errors + 1
            END IF
          END DO
        
          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .TRUE.
          END IF
        END
      END MODULE testmodule

      PROGRAM main
        USE testmodule
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1Result
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          test1Result = test1()
          failed = failed .or. test1Result
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT (failcode)
      END PROGRAM