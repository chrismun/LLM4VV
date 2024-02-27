!T1:cache directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8),DIMENSION(LOOPCOUNT),INTENT(IN) :: a, b, c
        REAL(8) :: s = 0
        INTEGER :: PRE_LOOP = LOOPCOUNT/128

        CALL RANDOM_SEED
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc data copy(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
          !$acc parallel
            !$acc cache(a(1:PRE_LOOP))
            !$acc loop
            DO i = 1, LOOPCOUNT
              c(i) = a(i) + b(i)
            END DO
          !$acc end parallel
        !$acc end data
        DO i = 1, LOOPCOUNT
          s = s + c(i) - (a(i) + b(i))
        END DO
        IF (s .ne. 0) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

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