#ifndef T1
!T1: host_data construct use_device clause, V:2.7-2.3
LOGICAL FUNCTION test1()
  USE OPENACC
  IMPLICIT NONE
  INCLUDE "acc_testsuite.Fh"

  INTEGER :: errors = 0
  INTEGER, DIMENSION(10):: a_host = (/ (i, i=1, 10) /)
  INTEGER, DIMENSION(10):: a_device
  INTEGER :: i
       
  a_device = a_host  ! Copy array to device using assignment statement
        
  !$ACC HOST_DATA USE_DEVICE(a_device)
    FOR i=1, 10
      IF (a_host(i) /= a_device(i)) THEN
        errors = errors + 1
      END IF
    END FOR
  !$ACC END HOST_DATA
  
  IF (errors .eq. 0) THEN
    test1 = .FALSE.
  ELSE
    test1 = .TRUE.
  END IF
END FUNCTION test1
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
END PROGRAM main