#ifndef T1
!T1:acc memcpy to device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(LOOPCOUNT):: host_array, devicecopy, devtest

        !initializing arrays
        devicecopy = 0
        host_array = 0
        devtest = 0

        !$acc enter data create(devicecopy(1:LOOPCOUNT))
        !$acc enter data create(devtest(1:LOOPCOUNT))

        DO testrun = 1, NUM_TEST_CALLS
          CALL RANDOM_SEED()
          CALL RANDOM_NUMBER(host_array)

          CALL acc_memcpy_to_device(devicecopy, host_array, LOOPCOUNT * sizeof(real))

          !$acc parallel
          !$acc loop
          DO I = 1, LOOPCOUNT
            devtest(I) = devicecopy(I)
          END DO
          !$acc end parallel

          DO I = 1, LOOPCOUNT
            IF (abs(host_array(I) - devtest(I)) .gt. PRECISION) THEN
              errors = errors + 1
              EXIT
            END IF
          END DO
        END DO

        DO I = 1, LOOPCOUNT
          IF (abs(devicecopy(I)) .gt. PRECISION) THEN
            errors = errors + 1
            EXIT
          END IF
        END DO

        DO I = 1, LOOPCOUNT
          IF (abs(devtest(I)) .gt. PRECISION) THEN
            errors = errors + 1
            EXIT
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