!T1:serial_construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: initial_array, array_copy
        REAL(8) :: multiplier = 3
        INTEGER :: x

        SEEDDIM(1) = 1
        initial_array = 0
        array_copy = initial_array

        DO x = 1, LOOPCOUNT
          initial_array(x) = 1 * x
          array_copy(x) = initial_array(x) * multiplier
        END DO          

        !$acc data copyin(initial_array(1:LOOPCOUNT)) copyout(array_copy(1:LOOPCOUNT))
          !$acc serial
            !$acc loop
            DO x = 1, LOOPCOUNT
              initial_array(x) = initial_array(x) * multiplier
            END DO
          !$acc end serial
        !$acc end data

        DO x = 1, LOOPCOUNT
          IF (abs(array_copy(x) - initial_array(x)) .gt. PRECISION) THEN
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
      END PROGRAM