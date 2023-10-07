#ifndef T1
!T1:serial construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

cDirective 1:"$acc serial"
      LOGICAL FUNCTION test1()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors, ia, ile, ub
        REAL(8), DIMENSION(LOOPCOUNT):: a
        INTEGER,DIMENSION(1):: test1
        test1 = 0
        errors = 0

        IF (acc_device_test(acc_device_nvidia)) THEN
          $acc enter data copyin(a(1:LOOPCOUNT))
          ia = 1
          ub = ia + LOOPCOUNT
          DO WHILE (ia .LE. ub)
            a(ia) = 0
            ia = ia + 1
          END DO

          !$acc serial if allocatable(a(:)) reduction(+:a)
          !$acc loop
          DO ia = 1, LOOPCOUNT
            a = a + 1
          END DO
          !$acc end serial

          ia = 1
          ile = LOOPCOUNT
          DO WHILE (a(mod(ia - 1, 24) + 1) .GT. 0 .AND. ia .LE. LOOPCOUNT)
            ia = ia + 1
          END DO
          IF (ia .LE. LOOPCOUNT) THEN
            IF (acc_device_test(IMPLEMENTATION_EXTENDED_PRECISION)) THEN
              IF (ia .eq. 13) THEN
                test1 = test1 + 1
              ELSE
                errors = errors + 1
              END IF
            ELSE
              IF (ia .eq. 10) THEN
                test1 = test1 + 1
              ELSE
                errors = errors + 1
              END IF
            END IF
          END IF

          $host  test1 =0


          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .FALSE.
          END IF
        ELSE
          test1 = .FALSE.
        END IF
      END