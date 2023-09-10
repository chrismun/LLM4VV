#ifndef T1
!T1:serial construct async clause,V:2.7-2.3
  LOGICAL FUNCTION test1()
    USE OPENACC
    IMPLICIT NONE
    INTEGER :: array1(10), array2(10), i
    INTEGER :: errors = 0

    DO i = 1, 10
      array1(i) = i
    END DO

    !$ACC ENTER DATA COPYIN(array1)

    !$ACC SERIAL ASYNC
      DO i = 1, 10
        array1(i) = array1(i) + 1
      END DO
    !$ACC END SERIAL

    !$ACC EXIT DATA COPYOUT(array1)

    call acc_wait_all()

    DO i = 1, 10
      IF (array1(i) .ne. i + 1) THEN
        errors = errors + 1
      END IF
    END DO

    IF (errors .eq. 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
  END FUNCTION test1
#endif

PROGRAM main
  USE OPENACC
  IMPLICIT NONE
  INTEGER :: failcode
  LOGICAL :: failed
#ifndef T1
  LOGICAL :: test1
#endif
  failed = .FALSE.
  failcode = 0
#ifndef T1
  LOGICAL, EXTERNAL :: test1
  failed = failed .or. test1()
  IF (failed) THEN
    failcode = failcode + 1
  END IF
#endif
  CALL EXIT (failcode)
END PROGRAM main