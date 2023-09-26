! Example for OpenACC Compiler Test on wait directive

#ifndef T1
!T1:wait directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER, DIMENSION(10) :: x, y, z
        INTEGER :: i
        INTEGER, ASYNCHRONOUS :: async_val1, async_val2

        x = (/ (i, i=1, 10) /)
        y = (/ (i, i=1, 10) /)
        z = (/ (0, i=1, 10) /)

        async_val1 = 1
        async_val2 = 2

        !$ACC PARALLEL LOOP ASYNC(async_val1)
        DO i = 1,10
          z(i) = x(i) + y(i)
        END DO

        !$ACC PARALLEL LOOP ASYNC(async_val2)
        DO i = 1,10
          z(i) = z(i) + y(i)
        END DO

        !$ACC WAIT(async_val1)
        !$ACC WAIT(async_val2)

        DO i = 1,10
          IF(z(i).NE.2*i) THEN
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
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        EXTERNAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. ( .NOT. test1() )
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main