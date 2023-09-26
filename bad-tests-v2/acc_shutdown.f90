#include "acc_testsuite.Fh"

LOGICAL FUNCTION test1()
  USE OPENACC
  IMPLICIT NONE
  INTEGER :: errors = 0

  ! Test acc_shutdown
  CALL acc_shutdown(acc_device_host)
  IF (acc_get_device_type() .NE. acc_device_host) THEN
    errors = errors + 1
  END IF

  ! Test acc_shutdown_device
  CALL acc_shutdown_device(1, acc_device_host)
  IF (acc_get_device_type(1) .NE. acc_device_host) THEN
    errors = errors + 1
  END IF

  IF (errors .EQ. 0) THEN
    test1 = .FALSE.
  ELSE
    test1 = .TRUE.
  END IF
END FUNCTION test1

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