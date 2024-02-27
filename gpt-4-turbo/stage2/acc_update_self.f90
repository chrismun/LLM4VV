!T1:acc update self,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(1024) :: arr
        INTEGER :: i

        ! Initialize array on the host
        DO i = 1, 1024
          arr(i) = i
        END DO

        ! Copy array to device and modify it on the device
        ! This is an example, for a real case, a computational kernel might be used
        !$acc enter data copyin(arr)
        !$acc parallel loop
        DO i = 1, 1024
          arr(i) = arr(i) + 1
        END DO
        !$acc end parallel loop
        !$acc exit data copyout(arr)

        ! Use acc_update_self to synchronize the modified array back to the host
        !$acc update self(arr)
       
        ! Verify modifications were made correctly
        ! This checks that the device modifications are visible on the host
        DO i = 1, 1024
          IF (arr(i) /= i + 1) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data delete(arr)

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