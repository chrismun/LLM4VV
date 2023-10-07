#ifndef T1
!T1:variable predetermined data attributes,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        ! OpenACC Loop Test
        DO CONCURRENT (x=1:NVL)
          IF (acc_get_device_type() == acc_device_gpu) THEN
            !$acc loop vector reduction(+:x)
            DO y = 1:10
              x = x + 1
            END DO
          END IF
        END DO
        !$acc parallel
        !$acc loop vector
        DO x = 1:NVL
          DO y = 1:acc_get_num_devices(acc_device_gpu)
            x[x][y] = x[x]
          END DO
        END DO
        !$acc end parallel
        DO CONCURRENT (x=1:NVL)
          IF (acc_get_device_type() == acc_device_gpu) THEN
            DO y = 1:10
              IF (x[x][y] == 0) THEN
                errors = errors + 1
              END IF
            END DO
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