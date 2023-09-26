#ifndef T1
!T1:acc detach,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        REAL(8),DIMENSION(LOOPCOUNT),DEVICE:: data
        INTEGER:: x
        
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        data = 0
        acc_attach(data)
        !$acc enter data create(data(1:LOOPCOUNT))
        
        !$acc data present(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT)) deviceptr(data)
          DO x = 1, LOOPCOUNT
            data(x) = a(x) + b(x)
          END DO
          DO x = 1, LOOPCOUNT
            c(x) = data(x)
          END DO
        !$acc end data
        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        CALL acc_detach_finalize(data)

        DO x = 1, LOOPCOUNT
          IF (abs(c(x)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        CALL acc_detach(data)

        !$acc exit data delete(data(1:LOOPCOUNT))

        DO x = 1, LOOPCOUNT
          IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
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