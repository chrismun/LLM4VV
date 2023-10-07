#ifndef T1
!T1:acc get device type,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: device_type
        INTEGER, PARAMETER :: NUM_DEVICE_KINDS = 5
        INTEGER, DIMENSION(1:NUM_DEVICE_KINDS) :: device_kinds = &
            [acc_device_none, acc_device_default, acc_device_host, acc_device_not_host, acc_device_nvptx]
        INTEGER :: k
        INTEGER :: errors = 0


        DO k = 1, NUM_DEVICE_KINDS
          CALL acc_set_device_type(device_kinds(k))
          device_type = acc_get_device_type()
          IF(device_type /= device_kinds(k)) THEN
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
      END