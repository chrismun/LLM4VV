#ifndef T1
!T1:acc copyout,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: host_array, device_array
        INTEGER :: i

        ! Initialize host_array
        DO i = 1, 10
          host_array(i) = i
        END DO

        !$acc enter data copyin(host_array)
        !$acc parallel present(host_array)
          !$acc loop
          DO i = 1, 10
            device_array(i) = host_array(i) + 1
          END DO
        !$acc end parallel

        !$acc update self(device_array)

        !$acc exit data delete(host_array)

        !$acc enter data copyin(device_array)
        !$acc parallel present(device_array)
          !$acc loop
          DO i = 1, 10
            host_array(i) = device_array(i) + 1
          END DO
        !$acc end parallel

        !$acc update self(host_array)

        !$acc exit data copyout(host_array)

        ! Check if the copyout was successful
        DO i = 1, 10
          IF (host_array(i) .ne. i + 2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM