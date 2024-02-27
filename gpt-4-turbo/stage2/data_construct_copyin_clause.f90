!T1:data construct copyin clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(10) :: hostArray
        INTEGER, DIMENSION(10) :: deviceArrayCopy
        INTEGER :: errors = 0
        INTEGER :: i

        ! Initialize hostArray with some values
        DO i = 1, 10
          hostArray(i) = i
        END DO

        ! Copy data into device memory and perform a dummy operation
        !$acc data copyin(hostArray)
            !$acc parallel loop
            DO i = 1, 10
                ! Copy into a separate array just for verification purposes
                deviceArrayCopy(i) = hostArray(i)
            END DO
        !$acc end parallel loop
        !$acc end data

        ! Check if the data was copied correctly
        DO i = 1, 10
          IF (deviceArrayCopy(i) /= hostArray(i)) THEN
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