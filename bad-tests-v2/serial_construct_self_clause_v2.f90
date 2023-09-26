#ifndef T1
!T1:serial construct self clause,V:2.7-2.3
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

        LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0, data(9), i


        !Initializations
        SEEDDIM(1) = 1
        #ifdef _OPENACC
           CALL RANDOM_SEED(PUT=SEEDDIM)
           CALL RANDOM_NUMBER (data)
        #endif
        i = 10
        data(i) = 1

        CALL _INIT(1, data(i))

        !$acc data copy(data(1:10))
          !$acc serial self ( i - 1)
            !$acc loop worker reduction (+: data(i))
            DO WHILE (i > 1)
              i = i - 1
            END DO
            !$acc loop worker
            DO WHILE (i > 0)
              data(i) = data(i) - 1
              i = i - 1
            END DO
          !$acc end serial
        !$acc end data

        DO CONCURRENT (i = 1 : 9)
          IF (data(i) .ne. 0) THEN
            errors = errors + 1
          END IF
        END DO
        IF (data(10) .ne. 1) THEN
          errors = errors + 1
        END IF

        !$acc exit data copyout(data(1:10))

        CALL _FINAL(1, data(10))

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END