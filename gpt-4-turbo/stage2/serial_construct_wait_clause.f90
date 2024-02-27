!T1:serial construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: data_on_host
        INTEGER, DIMENSION(10) :: data_on_device
        INTEGER :: i

        ! Initialize host and device data
        data_on_host = 0
        data_on_device = 0

        ! Parallel computation
        !$acc parallel loop copyout(data_on_device)
        DO i = 1, 10
          data_on_device(i) = i
        END DO

        ! Enforce serialization and wait for parallel region to complete
        !$acc serial wait copyin(data_on_device) copy(data_on_host)
        DO i = 1, 10
          data_on_host(i) = data_on_device(i) + 10
        END DO

        ! Verification
        DO i = 1, 10
          IF (data_on_host(i) /= i + 10) THEN
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