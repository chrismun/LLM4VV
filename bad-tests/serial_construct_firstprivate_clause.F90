#ifndef T1
!T1:serial construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: arr
        INTEGER, DIMENSION(SIZE(arr)) :: temp
        INTEGER :: i, data = 5

        arr = (/ (i, i=1,10) /)

        ! Here, an OpenACC serial region is created
        !$ACC SERIAL FIRSTPRIVATE(data)
        DO i = 1, SIZE(arr)
          arr(i) = arr(i) + data
        END DO
        !$ACC END SERIAL

        temp = arr - data

        DO i = 1, SIZE(temp)
          IF (temp(i) .NE. i) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
#ifndef T1
        LOGICAL :: test1
#endif
        INCLUDE "acc_testsuite.fh"
        failcode = 0
        failed = .FALSE.
#ifndef T1
     DO testrun = 1, NUM_TEST_CALLS
       failed = failed .or. .not. test1()
     END DO
     IF (failed) THEN
       failcode = failcode + 2 ** 0
     END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main